#pragma once
#include "TextBoxM.h"
#include <unordered_map>

enum class ActType {None, Reset, Giveup, Delete, Exit};  // action type

namespace Sudoku {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PlayForm
	/// </summary>
	public ref class PlayForm : public System::Windows::Forms::Form {
	public:
		PlayForm(Form^ selectForm, int gameId) {
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

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlayForm() {
			if (this->Visible) {
				GoBack();
			}

			DeleteVals();

			if (components) {
				delete components;
			}
		}

	private:
		Form^ selectForm;
		int gameId;
		Game* game;
		int size;
		char* availChars;
		int formWidth;
		int formHeight;
		int tableSize;
		int cellSize;
		int cellFontSize;
		TableLayoutPanel^ panelTable;
		int totalTabIndex;
		int* cellHashes;
		Collections::Generic::Dictionary<int, TextBoxM^>^ cells;
		int inserted;
		Color hlColor;
		Color repColor;
		Color nonRepColor;
		Timer^ cellTimer;
		Collections::Generic::List<TextBoxM^>^ changingCells;
		int changingCellsIndex;
		int fadeProgress;
		ActType currAction;

		void LoadGameObject() {
			game = Game::LoadFromDB(gameId);
		}

		void LoadVars() {
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

		void ResizeForm() {
			this->ClientSize = System::Drawing::Size(formWidth, formHeight);
		}

		System::String^ FormatDiff() {
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

		System::String^ FormatDate() {
			std::string sdate = game->dateCreated.to_string();
			int pos = sdate.find(' ');
			System::String^ newStr = conv(sdate.substr(0, pos) + "\r\n" + sdate.substr(pos + 1));
			return newStr;  // "2023/04/12\r\n14:05:24";
		}

		System::String^ FormatAvalChars(int sqrSize) {
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

		void ChangeInfo() {
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

			boxId->Location = Drawing::Point(5, formHeight-10-24);
			boxId->Text = L"ID: " + gameId;
		}

		void MoveButtons() {
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

		void CreateTable() {
			panelTable = gcnew System::Windows::Forms::TableLayoutPanel();

			panelTable->RowCount = 0;
			panelTable->ColumnCount = 0;
			panelTable->Location = System::Drawing::Point(160, 10);
			panelTable->Size = System::Drawing::Size(tableSize, tableSize);

			this->Controls->Add(panelTable);
		}

		TextBox^ CreateCell(int i, int j) {
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

		void FillTable() {
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

		void AddLine(int x, int y, int w, int h) {
			auto panel = gcnew Panel();

			panel->BackColor = Color::Black;
			panel->Enabled = false;
			panel->Location = Point(x, y);
			panel->Size = Drawing::Size(w, h);

			this->Controls->Add(panel);
			panel->BringToFront();
		}

		void AddLines() {
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

		void LoadUI() {
			ResizeForm();
			ChangeInfo();
			MoveButtons();
			CreateTable();
			FillTable();
			AddLines();
		}

		void OnError() {
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
			buttonBack->Location = Drawing::Point(25, 200-40);
			boxId->Location = Drawing::Point(25, 200-40-34);

			boxStatus->Text = L"Something went wrong when loading the game";
			boxId->Text = L"Game ID: " + gameId;
		}

		System::String^ ValidateText(TextBoxM^ textBox) {
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

		bool IsInSquare(TextBoxM^ tb, int sqrIdx) {
			if (game->FindSquareIndex(tb->tRow, tb->tCol) == sqrIdx) {
				return true;
			}
			else {
				return false;
			}
		}

		void StopTimer() {  // stops the fade out animation
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

		void LightDown(TextBoxM^ tb) {
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

		void LightUp(Validation vld) {
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

		int GetNewColor(int startColor, int endColor, int progress) {  // call this for R, G and B
			return startColor + ((endColor - startColor) * (progress / 100.0));
		}

		void MoveSelectionToEnd(TextBoxM^ tb) {
			tb->SelectionStart = tb->Text->Length;
			tb->SelectionLength = 0;
		}

		void OnLevelCompleted(CompletedStatus compStatus) {
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

		void CancelCurrAction(bool updateStatus, bool shiftFocusBack) {
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

		void AskForConfirmation(ActType action) {
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

		void ResetTable() {
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

		void GiveUp() {
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

		bool DeleteGame() {
			try {
				Game::DeleteFromDB(game->id);
				return true;
			}
			catch (exep& e) {
				logl(e.msg, true);
				return false;
			}
		}

		void DeleteVals() {
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

		void GoBack() {
			this->Hide();
			selectForm->Show();
		}

	private: System::Windows::Forms::Button^ buttonCancel;
	private: System::Windows::Forms::Button^ buttonConfirm;
	private: System::Windows::Forms::Button^ buttonValidate;
	private: System::Windows::Forms::Button^ buttonReset;
	private: System::Windows::Forms::Button^ buttonGiveup;
	private: System::Windows::Forms::Button^ buttonDelete;
	private: System::Windows::Forms::TextBox^ boxSize;
	private: System::Windows::Forms::Button^ buttonSave;
	private: System::Windows::Forms::TextBox^ boxDiff;
	private: System::Windows::Forms::TextBox^ boxDate;
	private: System::Windows::Forms::TextBox^ boxCharText;
	private: System::Windows::Forms::TextBox^ boxCompleted;
	private: System::Windows::Forms::TextBox^ boxChars;
	private: System::Windows::Forms::TextBox^ boxId;
	private: System::Windows::Forms::Button^ buttonBack;
	private: System::Windows::Forms::TextBox^ boxStatus;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonBack = (gcnew System::Windows::Forms::Button());
			this->boxStatus = (gcnew System::Windows::Forms::TextBox());
			this->buttonValidate = (gcnew System::Windows::Forms::Button());
			this->buttonReset = (gcnew System::Windows::Forms::Button());
			this->buttonGiveup = (gcnew System::Windows::Forms::Button());
			this->buttonDelete = (gcnew System::Windows::Forms::Button());
			this->boxSize = (gcnew System::Windows::Forms::TextBox());
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->boxDiff = (gcnew System::Windows::Forms::TextBox());
			this->boxDate = (gcnew System::Windows::Forms::TextBox());
			this->boxCharText = (gcnew System::Windows::Forms::TextBox());
			this->boxCompleted = (gcnew System::Windows::Forms::TextBox());
			this->boxChars = (gcnew System::Windows::Forms::TextBox());
			this->boxId = (gcnew System::Windows::Forms::TextBox());
			this->buttonConfirm = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonBack
			// 
			this->buttonBack->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonBack->Location = System::Drawing::Point(628, 340);
			this->buttonBack->Margin = System::Windows::Forms::Padding(4);
			this->buttonBack->Name = L"buttonBack";
			this->buttonBack->Size = System::Drawing::Size(150, 30);
			this->buttonBack->TabIndex = 5;
			this->buttonBack->Text = L"Exit";
			this->buttonBack->UseVisualStyleBackColor = true;
			this->buttonBack->Click += gcnew System::EventHandler(this, &PlayForm::buttonBack_Click);
			// 
			// boxStatus
			// 
			this->boxStatus->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxStatus->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 11));
			this->boxStatus->Location = System::Drawing::Point(628, 90);
			this->boxStatus->Margin = System::Windows::Forms::Padding(4);
			this->boxStatus->Multiline = true;
			this->boxStatus->Name = L"boxStatus";
			this->boxStatus->ReadOnly = true;
			this->boxStatus->Size = System::Drawing::Size(150, 80);
			this->boxStatus->TabIndex = 6;
			this->boxStatus->TabStop = false;
			this->boxStatus->Cursor = Cursors::Arrow;
			this->boxStatus->Text = L"Are you sure you want to reset the level\? Like, really sure\?";
			// 
			// buttonValidate
			// 
			this->buttonValidate->Location = System::Drawing::Point(628, 10);
			this->buttonValidate->Name = L"buttonValidate";
			this->buttonValidate->Size = System::Drawing::Size(150, 30);
			this->buttonValidate->TabIndex = 8;
			this->buttonValidate->Text = L"Validate";
			this->buttonValidate->UseVisualStyleBackColor = true;
			this->buttonValidate->Click += gcnew System::EventHandler(this, &PlayForm::buttonValidate_Click);
			// 
			// buttonReset
			// 
			this->buttonReset->Location = System::Drawing::Point(628, 220);
			this->buttonReset->Name = L"buttonReset";
			this->buttonReset->Size = System::Drawing::Size(150, 30);
			this->buttonReset->TabIndex = 8;
			this->buttonReset->Text = L"Reset level";
			this->buttonReset->UseVisualStyleBackColor = true;
			this->buttonReset->Click += gcnew System::EventHandler(this, &PlayForm::buttonReset_Click);
			// 
			// buttonGiveup
			// 
			this->buttonGiveup->Location = System::Drawing::Point(628, 260);
			this->buttonGiveup->Name = L"buttonGiveup";
			this->buttonGiveup->Size = System::Drawing::Size(150, 30);
			this->buttonGiveup->TabIndex = 8;
			this->buttonGiveup->Text = L"Give up";
			this->buttonGiveup->UseVisualStyleBackColor = true;
			this->buttonGiveup->Click += gcnew System::EventHandler(this, &PlayForm::buttonGiveup_Click);
			// 
			// buttonDelete
			// 
			this->buttonDelete->Location = System::Drawing::Point(628, 300);
			this->buttonDelete->Name = L"buttonDelete";
			this->buttonDelete->Size = System::Drawing::Size(150, 30);
			this->buttonDelete->TabIndex = 8;
			this->buttonDelete->Text = L"Delete level";
			this->buttonDelete->UseVisualStyleBackColor = true;
			this->buttonDelete->Click += gcnew System::EventHandler(this, &PlayForm::buttonDelete_Click);
			// 
			// boxSize
			// 
			this->boxSize->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxSize->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 13));
			this->boxSize->Location = System::Drawing::Point(5, 10);
			this->boxSize->Margin = System::Windows::Forms::Padding(4);
			this->boxSize->Multiline = true;
			this->boxSize->Name = L"boxSize";
			this->boxSize->ReadOnly = true;
			this->boxSize->Size = System::Drawing::Size(150, 24);
			this->boxSize->TabIndex = 6;
			this->boxSize->TabStop = false;
			this->boxSize->Cursor = Cursors::Arrow;
			this->boxSize->Text = L"Size: 9x9";
			// 
			// buttonSave
			// 
			this->buttonSave->Location = System::Drawing::Point(628, 50);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(150, 30);
			this->buttonSave->TabIndex = 8;
			this->buttonSave->Text = L"Save";
			this->buttonSave->UseVisualStyleBackColor = true;
			this->buttonSave->Click += gcnew System::EventHandler(this, &PlayForm::buttonSave_Click);
			// 
			// boxDiff
			// 
			this->boxDiff->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxDiff->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 13));
			this->boxDiff->Location = System::Drawing::Point(5, 44);
			this->boxDiff->Margin = System::Windows::Forms::Padding(4);
			this->boxDiff->Multiline = true;
			this->boxDiff->Name = L"boxDiff";
			this->boxDiff->ReadOnly = true;
			this->boxDiff->Size = System::Drawing::Size(150, 24);
			this->boxDiff->TabIndex = 9;
			this->boxDiff->TabStop = false;
			this->boxDiff->Cursor = Cursors::Arrow;
			this->boxDiff->Text = L"Difficulty: Medium";
			// 
			// boxDate
			// 
			this->boxDate->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxDate->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 13));
			this->boxDate->Location = System::Drawing::Point(5, 78);
			this->boxDate->Margin = System::Windows::Forms::Padding(4);
			this->boxDate->Multiline = true;
			this->boxDate->Name = L"boxDate";
			this->boxDate->ReadOnly = true;
			this->boxDate->Size = System::Drawing::Size(150, 72);
			this->boxDate->TabIndex = 10;
			this->boxDate->TabStop = false;
			this->boxDate->Cursor = Cursors::Arrow;
			this->boxDate->Text = L"Date created:\r\n2023/04/12\r\n14:05:24";
			// 
			// boxCompleted
			// 
			this->boxCompleted->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxCompleted->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 13));
			this->boxCompleted->Location = System::Drawing::Point(5, 160);
			this->boxCompleted->Margin = System::Windows::Forms::Padding(4);
			this->boxCompleted->Multiline = true;
			this->boxCompleted->Name = L"boxCompleted";
			this->boxCompleted->ReadOnly = true;
			this->boxCompleted->Size = System::Drawing::Size(150, 48);
			this->boxCompleted->TabIndex = 11;
			this->boxCompleted->TabStop = false;
			this->boxCompleted->Cursor = Cursors::Arrow;
			this->boxCompleted->Text = L"Has not been completed";
			// 
			// boxCharText
			// 
			this->boxCharText->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxCharText->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 13));
			this->boxCharText->Location = System::Drawing::Point(5, 218);
			this->boxCharText->Margin = System::Windows::Forms::Padding(4);
			this->boxCharText->Multiline = true;
			this->boxCharText->Name = L"boxCharText";
			this->boxCharText->ReadOnly = true;
			this->boxCharText->Size = System::Drawing::Size(150, 48);
			this->boxCharText->TabIndex = 11;
			this->boxCharText->TabStop = false;
			this->boxCharText->Cursor = Cursors::Arrow;
			this->boxCharText->Text = L"Available characters:";
			// 
			// boxChars
			// 
			this->boxChars->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxChars->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 14, System::Drawing::FontStyle::Bold));
			this->boxChars->Location = System::Drawing::Point(5, 266);
			this->boxChars->Margin = System::Windows::Forms::Padding(4);
			this->boxChars->Multiline = true;
			this->boxChars->Name = L"boxChars";
			this->boxChars->ReadOnly = true;
			this->boxChars->Size = System::Drawing::Size(150, 95);
			this->boxChars->TabIndex = 12;
			this->boxChars->TabStop = false;
			this->boxChars->Text = L"1  2  3\r\n4  5  6\r\n7  8  9";
			this->boxChars->Cursor = Cursors::Arrow;
			this->boxChars->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// boxId
			// 
			this->boxId->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxId->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 13));
			this->boxId->Location = System::Drawing::Point(5, 346);
			this->boxId->Margin = System::Windows::Forms::Padding(4);
			this->boxId->Multiline = true;
			this->boxId->Name = L"boxId";
			this->boxId->ReadOnly = true;
			this->boxId->Size = System::Drawing::Size(150, 24);
			this->boxId->TabIndex = 13;
			this->boxId->TabStop = false;
			this->boxId->Cursor = Cursors::Arrow;
			this->boxId->Text = L"ID: 534";
			// 
			// buttonConfirm
			// 
			this->buttonConfirm->Enabled = false;
			this->buttonConfirm->Location = System::Drawing::Point(628, 180);
			this->buttonConfirm->Name = L"buttonConfirm";
			this->buttonConfirm->Size = System::Drawing::Size(150, 30);
			this->buttonConfirm->TabIndex = 14;
			this->buttonConfirm->Text = L"Confirm";
			this->buttonConfirm->UseVisualStyleBackColor = true;
			this->buttonConfirm->Click += gcnew System::EventHandler(this, &PlayForm::buttonConfirm_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Enabled = false;
			this->buttonCancel->Location = System::Drawing::Point(0, 0);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(150, 30);
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &PlayForm::buttonCancel_Click);
			// 
			// PlayForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(784, 380);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonConfirm);
			this->Controls->Add(this->boxId);
			this->Controls->Add(this->boxChars);
			this->Controls->Add(this->boxCharText);
			this->Controls->Add(this->boxCompleted);
			this->Controls->Add(this->boxDate);
			this->Controls->Add(this->boxDiff);
			this->Controls->Add(this->buttonDelete);
			this->Controls->Add(this->buttonGiveup);
			this->Controls->Add(this->buttonReset);
			this->Controls->Add(this->buttonSave);
			this->Controls->Add(this->buttonValidate);
			this->Controls->Add(this->boxSize);
			this->Controls->Add(this->boxStatus);
			this->Controls->Add(this->buttonBack);
			this->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"PlayForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sudoku | Play";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void cell_TextChanged(System::Object^ sender, System::EventArgs^ e) {
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

private: System::Void buttonValidate_Click(System::Object^ sender, System::EventArgs^ e) {
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

private: System::Void TimerTick(Object^ sender, EventArgs^ e) {  // https://stackoverflow.com/a/40978799
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

private: System::Void cell_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	MoveSelectionToEnd(cells[sender->GetHashCode()]);
}

private: System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e) {
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

private: System::Void buttonConfirm_Click(System::Object^ sender, System::EventArgs^ e) {
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

private: System::Void buttonReset_Click(System::Object^ sender, System::EventArgs^ e) {
	AskForConfirmation(ActType::Reset);
}

private: System::Void buttonGiveup_Click(System::Object^ sender, System::EventArgs^ e) {
	AskForConfirmation(ActType::Giveup);
}

private: System::Void buttonDelete_Click(System::Object^ sender, System::EventArgs^ e) {
	AskForConfirmation(ActType::Delete);
}

private: System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
	AskForConfirmation(ActType::Exit);
}

private: System::Void buttonCancel_Click(System::Object^ sender, System::EventArgs^ e) {
	CancelCurrAction(true, true);
}

};
}
