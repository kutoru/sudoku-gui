#include "PlayForm.h"

namespace Sudoku {
	PlayForm::PlayForm(Form^ selectForm, int gameId) {
		InitializeComponent();

		this->selectForm = selectForm;
		this->gameId = gameId;

		this->totalTabIndex = 0;
		this->changingCellsIndex = 0;

		this->cells = nullptr;
		this->game = nullptr;
		this->availChars = nullptr;
		this->cellHashes = nullptr;
		this->changingCells = nullptr;

		// colors for: highlighted cells, cells with replaceable values, cells with non-replaceable values
		this->hlColor = Color::FromArgb(255, 100, 100);
		this->repColor = Color::White;
		this->nonRepColor = Color::LightGray;

		this->cellTimer = gcnew Timer();
		this->cellTimer->Interval = 33;  // thats around 30 fps
		this->cellTimer->Tick += gcnew System::EventHandler(this, &Sudoku::PlayForm::TimerTick);

		this->currAction = ActType::None;
		this->buttonCancel->Hide();
		this->boxStatus->Text = L"";

		try {
			DeleteVals();
			LoadGameObject();
			LoadVars();
			LoadUI();
		}
		catch (exep& e) {
			logl(e.msg, true);
			OnError();
		}
	}

	PlayForm::~PlayForm() {
		if (this->Visible) {
			GoBack();
		}

		DeleteVals();

		if (components) {
			delete components;
		}
	}

	void PlayForm::LoadGameObject() {
		game = Game::LoadFromDB(gameId);
	}

	void PlayForm::LoadVars() {
		size = game->size;
		formWidth = 5 + 150 + 5 + 5 + 150 + 5;
		formHeight = 10 + 10;

		if (size == 4) {
			tableSize = 240;
			cellSize = 60;
			cellFontSize = 29;
			formWidth += tableSize;
			formHeight += 360;
		}

		else if (size == 9) {
			tableSize = 360;
			cellSize = 40;
			cellFontSize = 19;
			formWidth += tableSize;
			formHeight += tableSize;
		}

		else if (size == 16) {
			tableSize = 480;
			cellSize = 30;
			cellFontSize = 14;
			formWidth += tableSize;
			formHeight += tableSize;
		}

		availChars = new char[size];
		changingCells = gcnew Collections::Generic::List<TextBoxM^>(size);
		for (int i = 0; i < size; i++) {
			availChars[i] = game->totalChars[i];
			changingCells->Add(nullptr);
		}
	}

	void PlayForm::ResizeForm() {
		this->ClientSize = System::Drawing::Size(formWidth, formHeight);
	}

	System::String^ PlayForm::FormatDiff() {
		if (game->difficulty == Difficulty::Easy) {
			return L"Easy";
		}
		else if (game->difficulty == Difficulty::Medium) {
			return L"Medium";
		}
		else if (game->difficulty == Difficulty::Hard) {
			return L"Hard";
		}
	}

	System::String^ PlayForm::FormatDate() {
		std::string sdate = game->dateCreated.to_string();
		int pos = sdate.find(' ');
		System::String^ newStr = conv(sdate.substr(0, pos) + "\r\n" + sdate.substr(pos + 1));
		return newStr;  // "2023/04/12\r\n14:05:24";
	}

	System::String^ PlayForm::FormatAvalChars(int sqrSize) {
		std::string newStr;

		for (int i = 0; i < sqrSize; i++) {
			if (i > 0) {
				newStr += "\r\n";
			}

			for (int j = 0; j < sqrSize; j++) {
				if (j > 0) {
					newStr += "   ";
				}

				newStr += availChars[i * sqrSize + j];
			}
		}

		return conv(newStr);
	}

	void PlayForm::ChangeInfo() {
		int sqrSize = pow(size, 0.5);

		boxSize->Text = L"Size: " + size + "x" + size;
		boxDiff->Text = L"Difficulty: " + FormatDiff();
		boxDate->Text = L"Date created:\r\n" + FormatDate();

		if (game->completed == CompletedStatus::No) {
			boxCompleted->Text = L"Has not been completed";
		}
		else if (game->completed == CompletedStatus::Yes) {
			boxCompleted->Text = L"Has been completed";
		}
		else if (game->completed == CompletedStatus::Gaveup) {
			boxCompleted->Text = L"Has given up";
		}

		boxChars->Height = 31 * sqrSize;
		boxChars->Text = FormatAvalChars(sqrSize);

		boxId->Location = Drawing::Point(5, formHeight - 10 - 24);
		boxId->Text = L"ID: " + gameId;
	}

	void PlayForm::MoveButtons() {
		int xPos = formWidth - 5 - 150;

		buttonValidate->Location = Drawing::Point(xPos, 10);
		buttonSave->Location = Drawing::Point(xPos, 50);
		boxStatus->Location = Drawing::Point(xPos, 90);

		buttonConfirm->Location = Drawing::Point(xPos, formHeight - 200);
		buttonReset->Location = Drawing::Point(xPos, formHeight - 160);
		buttonGiveup->Location = Drawing::Point(xPos, formHeight - 120);
		buttonDelete->Location = Drawing::Point(xPos, formHeight - 80);
		buttonBack->Location = Drawing::Point(xPos, formHeight - 40);

		buttonValidate->TabIndex = totalTabIndex++;
		buttonSave->TabIndex = totalTabIndex++;
		buttonConfirm->TabIndex = totalTabIndex++;
		buttonReset->TabIndex = totalTabIndex++;
		buttonGiveup->TabIndex = totalTabIndex++;
		buttonDelete->TabIndex = totalTabIndex++;
		buttonBack->TabIndex = totalTabIndex++;
	}

	void PlayForm::CreateTable() {
		panelTable = gcnew System::Windows::Forms::TableLayoutPanel();

		panelTable->RowCount = 0;
		panelTable->ColumnCount = 0;
		panelTable->Location = System::Drawing::Point(160, 10);
		panelTable->Size = System::Drawing::Size(tableSize, tableSize);

		this->Controls->Add(panelTable);
	}

	TextBox^ PlayForm::CreateCell(int i, int j) {
		bool replaceable = game->CharIsReplaceable(i, j);
		char value = game->GetChar(i, j);
		if (value == game->emptyChar) {
			value = NULL;
		}
		else if (replaceable) {  // keeping track of inserted values
			inserted++;
		}

		TextBoxM^ newCell = gcnew TextBoxM(i, j, value, replaceable);

		if (replaceable) {
			newCell->Font = gcnew Drawing::Font(L"Yu Gothic UI", cellFontSize, Drawing::FontStyle::Regular, Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));
			newCell->TabIndex = totalTabIndex++;
			newCell->TextChanged += gcnew System::EventHandler(this, &PlayForm::cell_TextChanged);
			newCell->BackColor = repColor;
		}
		else {
			newCell->ReadOnly = true;
			newCell->Font = gcnew Drawing::Font(L"Yu Gothic UI", cellFontSize, Drawing::FontStyle::Bold, Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));
			newCell->TabStop = false;
			newCell->BackColor = nonRepColor;
		}

		newCell->Location = System::Drawing::Point(0, 0);
		newCell->Margin = System::Windows::Forms::Padding(0);
		newCell->Multiline = true;
		newCell->Size = System::Drawing::Size(cellSize, cellSize);
		newCell->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		newCell->Cursor = Cursors::Arrow;
		newCell->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PlayForm::cell_MouseDown);

		int hash = newCell->GetHashCode();
		cellHashes[i * size + j] = hash;
		cells[hash] = newCell;

		return newCell;
	}

	void PlayForm::FillTable() {
		cells = gcnew Collections::Generic::Dictionary<int, TextBoxM^>();
		cellHashes = new int[size * size];

		for (int i = 0; i < size; i++) {
			panelTable->RowCount += 1;
			panelTable->RowStyles->Add((gcnew RowStyle(SizeType::Absolute, cellSize)));

			for (int j = 0; j < size; j++) {
				panelTable->ColumnCount += 1;
				panelTable->ColumnStyles->Add((gcnew ColumnStyle(SizeType::Absolute, cellSize)));

				panelTable->Controls->Add(CreateCell(j, i), i, j);
			}
		}
	}

	void PlayForm::AddLine(int x, int y, int w, int h) {
		auto panel = gcnew Panel();

		panel->BackColor = Color::Black;
		panel->Enabled = false;
		panel->Location = Point(x, y);
		panel->Size = Drawing::Size(w, h);

		this->Controls->Add(panel);
		panel->BringToFront();
	}

	void PlayForm::AddLines() {
		int sqrSize = pow(size, 0.5);

		// horizontal
		for (int i = 0; i <= sqrSize; i++) {
			int x = 5 + 150 + 5 - 2;
			int y = (cellSize * i * sqrSize) + 10 - 2;
			int w = tableSize + 4;
			int h = 4;
			AddLine(x, y, w, h);
		}

		// vertical
		for (int i = 0; i <= sqrSize; i++) {
			auto panel = gcnew Panel();
			int x = (cellSize * i * sqrSize) + 5 + 150 + 5 - 2;
			int y = 10 - 2;
			int w = 4;
			int h = tableSize + 4;
			AddLine(x, y, w, h);
		}
	}

	void PlayForm::LoadUI() {
		ResizeForm();
		ChangeInfo();
		MoveButtons();
		CreateTable();
		FillTable();
		AddLines();
	}

	void PlayForm::OnError() {
		buttonConfirm->Hide();
		buttonValidate->Hide();
		buttonReset->Hide();
		buttonGiveup->Hide();
		buttonDelete->Hide();
		boxSize->Hide();
		buttonSave->Hide();
		boxDiff->Hide();
		boxDate->Hide();
		boxCompleted->Hide();
		boxCharText->Hide();
		boxChars->Hide();

		formWidth = 200;
		formHeight = 200;
		ResizeForm();

		boxStatus->Location = Drawing::Point(25, 10);
		buttonBack->Location = Drawing::Point(25, 200 - 40);
		boxId->Location = Drawing::Point(25, 200 - 40 - 34);

		boxStatus->Text = L"Something went wrong when loading the game";
		boxId->Text = L"Game ID: " + gameId;
	}

	System::String^ PlayForm::ValidateText(TextBoxM^ textBox) {
		auto text = textBox->Text;
		char charToCheck;

		if (text->Length == 0) {
			return text;
		}
		else if (text->Length == 1) {
			charToCheck = text[0];
		}
		else if (text->Length == 2 && textBox->prevChar->Length == 1) {
			charToCheck = text[0];
			if (charToCheck == textBox->prevChar[0]) {
				charToCheck = text[1];
			}
		}
		else {
			return textBox->prevChar;
		}

		charToCheck = toupper(charToCheck);
		for (int i = 0; i < size; i++) {
			if (availChars[i] == charToCheck) {
				return conv(charToCheck);
			}
		}

		return textBox->prevChar;
	}

	bool PlayForm::IsInSquare(TextBoxM^ tb, int sqrIdx) {
		if (game->FindSquareIndex(tb->tRow, tb->tCol) == sqrIdx) {
			return true;
		}
		else {
			return false;
		}
	}

	void PlayForm::StopTimer() {  // stops the fade out animation
		cellTimer->Stop();
		for (int i = 0; i < size; i++) {
			auto tb = changingCells[i];
			changingCells[i] = nullptr;

			if (tb->replaceable) {
				tb->BackColor = repColor;
			}
			else {
				tb->BackColor = nonRepColor;
			}
		}
		changingCellsIndex = 0;
	}

	void PlayForm::LightDown(TextBoxM^ tb) {
		if (changingCellsIndex == size) {
			StopTimer();
		}

		changingCells[changingCellsIndex] = tb;
		changingCellsIndex++;

		if (changingCellsIndex == size) {
			fadeProgress = 0;
			cellTimer->Start();
		}
	}

	void PlayForm::LightUp(Validation vld) {
		int litUp = 0;

		if (vld.vldType == ValidationType::Row) {
			for (int i = 0; i < size * size; i++) {
				auto tb = cells[cellHashes[i]];
				if (tb->tRow == vld.insRow) {
					tb->BackColor = hlColor;
					LightDown(tb);
					litUp++;
				}
				if (litUp == size) {
					return;
				}
			}
		}

		else if (vld.vldType == ValidationType::Col) {
			for (int i = 0; i < size * size; i++) {
				auto tb = cells[cellHashes[i]];
				if (tb->tCol == vld.insCol) {
					tb->BackColor = hlColor;
					LightDown(tb);
					litUp++;
				}
				if (litUp == size) {
					return;
				}
			}
		}

		else if (vld.vldType == ValidationType::Sqr) {
			for (int i = 0; i < size * size; i++) {
				auto tb = cells[cellHashes[i]];
				if (IsInSquare(tb, vld.sqrIdx)) {
					tb->BackColor = hlColor;
					LightDown(tb);
					litUp++;
				}
				if (litUp == size) {
					return;
				}
			}
		}
	}

	int PlayForm::GetNewColor(int startColor, int endColor, int progress) {  // call this for R, G and B
		return startColor + ((endColor - startColor) * (progress / 100.0));
	}

	void PlayForm::MoveSelectionToEnd(TextBoxM^ tb) {
		tb->SelectionStart = tb->Text->Length;
		tb->SelectionLength = 0;
	}

	void PlayForm::OnLevelCompleted(CompletedStatus compStatus) {
		if (game->completed == CompletedStatus::Yes || game->completed == CompletedStatus::Gaveup) {
			return;
		}

		game->completed = compStatus;

		if (game->completed == CompletedStatus::Yes) {
			boxCompleted->Text = L"Has been completed";
		}
		else if (game->completed == CompletedStatus::Gaveup) {
			boxCompleted->Text = L"Has given up";
		}

		try {
			Game::SaveGame(game);
		}
		catch (exep& e) {
			logl(e.msg, true);

			if (boxStatus->Text->Length > 0) {
				boxStatus->Text += L". ";
			}
			boxStatus->Text += L"Something went wrong when saving the game";
		}
	}

	void PlayForm::CancelCurrAction(bool updateStatus, bool shiftFocusBack) {
		if (currAction == ActType::None) {
			return;
		}

		Button^ actionButton;

		if (currAction == ActType::Reset) {
			actionButton = buttonReset;
		}
		else if (currAction == ActType::Giveup) {
			actionButton = buttonGiveup;
		}
		else if (currAction == ActType::Delete) {
			actionButton = buttonDelete;
		}
		else if (currAction == ActType::Exit) {
			actionButton = buttonBack;
		}

		if (updateStatus) {
			boxStatus->Text = L"Cancelled";
		}

		buttonConfirm->Enabled = false;

		buttonCancel->Enabled = false;
		buttonCancel->Hide();

		currAction = ActType::None;

		actionButton->Enabled = true;
		actionButton->Show();

		if (shiftFocusBack) {
			actionButton->Focus();
		}
	}

	void PlayForm::AskForConfirmation(ActType action) {
		if (currAction != ActType::None) {
			CancelCurrAction(false, false);
		}

		Button^ actionButton;

		if (action == ActType::Reset) {
			boxStatus->Text = L"Are you sure you want to reset the level?";
			actionButton = buttonReset;
		}
		else if (action == ActType::Giveup) {
			boxStatus->Text = L"Are you sure you want to give up?";
			actionButton = buttonGiveup;
		}
		else if (action == ActType::Delete) {
			boxStatus->Text = L"Are you sure you want to delete the level?";
			actionButton = buttonDelete;
		}
		else if (action == ActType::Exit) {
			boxStatus->Text = L"Are you sure you want to exit? Don't forget to save before exiting";
			actionButton = buttonBack;
		}

		actionButton->Enabled = false;
		actionButton->Hide();

		buttonCancel->Location = actionButton->Location;
		buttonCancel->TabIndex = actionButton->TabIndex;

		currAction = action;

		buttonCancel->Enabled = true;
		buttonCancel->Show();

		buttonCancel->Focus();

		buttonConfirm->Enabled = true;
	}

	void PlayForm::ResetTable() {
		for (int i = 0; i < size * size; i++) {
			auto tb = cells[cellHashes[i]];

			if (tb->replaceable && tb->Text->Length == 1) {
				tb->Text = L"";
				tb->prevChar = L"";
			}
		}

		game->ResetLevel();

		boxStatus->Text = L"The level has been reset";
	}

	void PlayForm::GiveUp() {
		game->SolveLevel();

		for (int i = 0; i < size * size; i++) {
			auto tb = cells[cellHashes[i]];

			if (tb->replaceable) {
				System::String^ ch = conv(game->GetChar(tb->tRow, tb->tCol));
				tb->Text = ch;
				tb->prevChar = ch;
			}
		}

		boxStatus->Text = L"Solved the level";
		OnLevelCompleted(CompletedStatus::Gaveup);
	}

	bool PlayForm::DeleteGame() {
		try {
			Game::DeleteFromDB(game->id);
			return true;
		}
		catch (exep& e) {
			logl(e.msg, true);
			return false;
		}
	}

	void PlayForm::DeleteVals() {
		if (cells != nullptr) {
			delete cells;
			cells = nullptr;
		}
		if (cellHashes != nullptr) {
			delete[] cellHashes;
			cellHashes = nullptr;
		}
		if (game != nullptr) {
			delete game;
			game = nullptr;
		}
		if (availChars != nullptr) {
			delete[] availChars;
			availChars = nullptr;
		}
	}

	void PlayForm::GoBack() {
		this->Hide();
		selectForm->Show();
	}

	// BOTTOM FUNCTIONS

	System::Void PlayForm::cell_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		auto textBox = cells[sender->GetHashCode()];
		auto charToSet = ValidateText(textBox);

		if (charToSet->Length == 1) {
			game->SetChar(textBox->tRow, textBox->tCol, charToSet[0]);
		}
		else {
			game->SetChar(textBox->tRow, textBox->tCol, game->emptyChar);
		}

		if (charToSet->Length == 0 && textBox->prevChar->Length == 1) {
			inserted--;
		}
		else if (charToSet->Length == 1 && textBox->prevChar->Length == 0) {
			inserted++;
		}

		textBox->Text = charToSet;
		textBox->prevChar = charToSet;

		MoveSelectionToEnd(textBox);
	}

	System::Void PlayForm::buttonValidate_Click(System::Object^ sender, System::EventArgs^ e) {
		CancelCurrAction(false, false);

		auto vld = game->ValidateLevel();

		if (vld.foundDupe) {
			boxStatus->Text = L"Found an incorrect value at:\r\nRow: " + (vld.insRow + 1) + "; Column: " + (vld.insCol + 1) + ";";

			if (vld.vldType == ValidationType::Row)
				boxStatus->Text += L"\r\nThe row is invalid";
			if (vld.vldType == ValidationType::Col)
				boxStatus->Text += L"\r\nThe column is invalid";
			if (vld.vldType == ValidationType::Sqr)
				boxStatus->Text += L"\r\nThe square is invalid";

			LightUp(vld);
		}

		else {
			if (inserted == game->removeAmount) {
				boxStatus->Text = L"You have completed the level";
				OnLevelCompleted(CompletedStatus::Yes);
			}
			else {
				boxStatus->Text = L"All inserted values are correct";
			}
		}
	}

	System::Void PlayForm::TimerTick(Object^ sender, EventArgs^ e) {  // https://stackoverflow.com/a/40978799
		fadeProgress += 2;  // fade out duration = 100 / 2 * timer->Interval

		if (fadeProgress >= 100) {
			StopTimer();
			return;
		}

		int finalR, finalG, finalB;
		int newR, newG, newB;
		for (int i = 0; i < size; i++) {
			auto tb = changingCells[i];

			if (tb->replaceable) {
				finalR = repColor.R;
				finalG = repColor.G;
				finalB = repColor.B;
			}
			else {
				finalR = nonRepColor.R;
				finalG = nonRepColor.G;
				finalB = nonRepColor.B;
			}

			newR = GetNewColor(hlColor.R, finalR, fadeProgress);
			newG = GetNewColor(hlColor.G, finalG, fadeProgress);
			newB = GetNewColor(hlColor.B, finalB, fadeProgress);

			tb->BackColor = Color::FromArgb(newR, newG, newB);
		}
	}

	System::Void PlayForm::cell_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		MoveSelectionToEnd(cells[sender->GetHashCode()]);
	}

	System::Void PlayForm::buttonSave_Click(System::Object^ sender, System::EventArgs^ e) {
		CancelCurrAction(false, false);

		try {
			Game::SaveGame(game);
			boxStatus->Text = L"The level has been saved";
		}
		catch (exep& e) {
			logl(e.msg, true);
			boxStatus->Text = L"Something went wrong when saving the level";
		}
	}

	System::Void PlayForm::buttonConfirm_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currAction == ActType::Reset) {
			ResetTable();
			CancelCurrAction(false, true);
		}
		else if (currAction == ActType::Giveup) {
			GiveUp();
			CancelCurrAction(false, true);
		}
		else if (currAction == ActType::Delete) {
			bool gotDeleted = DeleteGame();
			if (gotDeleted) {
				GoBack();
			}
			else {
				boxStatus->Text = L"Something went wrong when deleting the game, it might be corrupted now";
				CancelCurrAction(false, true);
			}
		}
		else if (currAction == ActType::Exit) {
			GoBack();
		}
	}

	System::Void PlayForm::buttonReset_Click(System::Object^ sender, System::EventArgs^ e) {
		AskForConfirmation(ActType::Reset);
	}

	System::Void PlayForm::buttonGiveup_Click(System::Object^ sender, System::EventArgs^ e) {
		AskForConfirmation(ActType::Giveup);
	}

	System::Void PlayForm::buttonDelete_Click(System::Object^ sender, System::EventArgs^ e) {
		AskForConfirmation(ActType::Delete);
	}

	System::Void PlayForm::buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
		AskForConfirmation(ActType::Exit);
	}

	System::Void PlayForm::buttonCancel_Click(System::Object^ sender, System::EventArgs^ e) {
		CancelCurrAction(true, true);
	}
}
