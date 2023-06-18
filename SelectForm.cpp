#include "SelectForm.h"

namespace Sudoku {
	// TOP FUNCTIONS

	SelectForm::SelectForm(Form^ menuForm, int accId) {
		InitializeComponent();

		this->menuForm = menuForm;
		this->accId = accId;
		this->playForm = nullptr;
		this->buttons = nullptr;
		this->btnHashes = nullptr;
	}

	SelectForm::~SelectForm() {
		if (this->Visible) {
			GoBack();
		}

		DeleteEntries();

		if (components) {
			delete components;
		}
	}

	Button^ SelectForm::CreateEntry(int btnIndex, int gameId, CompletedStatus completed, int size, char diff, std::string sdate) {  // future arguments will be: gameId, completion, size, etc
		Button^ newButton = gcnew Button();

		// formatting the button text

		if (completed == CompletedStatus::No) {
			newButton->Text = L"Not completed; ";
		}
		else if (completed == CompletedStatus::Yes) {
			newButton->Text = L"Completed; ";
		}
		else if (completed == CompletedStatus::Gaveup) {
			newButton->Text = L"Gave up; ";
		}

		newButton->Text += "Size: " + size + "x" + size + "; ";

		newButton->Text += "Difficulty: ";
		if (diff == 'E') {
			newButton->Text += "Easy;\r\n";
		}
		else if (diff == 'M') {
			newButton->Text += "Medium;\r\n";
		}
		else if (diff == 'H') {
			newButton->Text += "Hard;\r\n";
		}

		newButton->Text += "Date created: " + conv(sdate) + ";";

		// applying other settings

		newButton->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 10));
		newButton->Size = System::Drawing::Size(352, 47);  // 332 with scrollbar and 352 without
		newButton->TabIndex = btnIndex + 1;
		newButton->TextAlign = System::Drawing::ContentAlignment::TopLeft;
		newButton->UseVisualStyleBackColor = true;
		newButton->Click += gcnew System::EventHandler(this, &SelectForm::buttonEntry_Click);

		buttons->Add(newButton);
		(*btnHashes)[newButton->GetHashCode()] = gameId;

		return newButton;
	}

	TextBox^ SelectForm::CreateStatus() {
		TextBox^ boxStatus = gcnew TextBox();

		boxStatus->BorderStyle = System::Windows::Forms::BorderStyle::None;
		boxStatus->ReadOnly = true;
		boxStatus->Size = System::Drawing::Size(352, 47);
		boxStatus->TabStop = false;
		boxStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		boxStatus->Text = L"No games were found. Go back and create some";

		return boxStatus;
	}

	void SelectForm::LoadBasicGameInfo() {
		db.query << "select `id`, `completed`, `size`, `difficulty`, `date_created` from games where user_id = " << accId << " order by `id` desc;";
		db.load_res();
	}

	void SelectForm::GetRowInfo(int& gameId, CompletedStatus& completed, int& size, char& diff, std::string& sdate) {
		auto row = db.get_row();

		if (row) {
			gameId = atoi(row[0]);
			completed = convCompStat(*row[1]);
			size = atoi(row[2]);
			diff = *row[3];
			sdate = row[4];
		}
		else {
			gameId = 0;
		}
	}

	void SelectForm::Populate() {
		if (buttons != nullptr || btnHashes != nullptr) {
			DeleteEntries();
		}
		buttons = gcnew System::Collections::Generic::List<Button^>();
		btnHashes = new std::unordered_map<int, int>();

		Button^ btn;
		int i;

		int gameId;
		CompletedStatus completed;
		int size;
		char diff;
		std::string sdate;

		LoadBasicGameInfo();
		GetRowInfo(gameId, completed, size, diff, sdate);

		for (i = 0; gameId != 0; i++) {
			btn = CreateEntry(i, gameId, completed, size, diff, sdate);
			panelTable->RowCount += 1;
			panelTable->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
			panelTable->Controls->Add(btn, 0, i);
			GetRowInfo(gameId, completed, size, diff, sdate);
		}

		buttonBack->TabIndex = i + 2;

		if (i == 0) {
			panelTable->RowCount += 1;
			panelTable->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
			panelTable->Controls->Add(CreateStatus(), 0, i);
		}
		else if (i > 7) {  // 7 is max button count without having to add the scrollbar
			EnablePanelScroll();
			for (i -= 1; i >= 0; i--) {
				buttons[i]->Width = 332;
			}
		}
	}

	void SelectForm::DeleteEntries() {
		if (btnHashes != nullptr) {
			delete btnHashes;
			btnHashes = nullptr;
		}

		if (buttons != nullptr) {
			for (int i = 0; i < buttons->Count; i++) {
				delete buttons[i];
			}

			delete buttons;
			buttons = nullptr;
		}
	}

	void SelectForm::EnablePanelScroll() {  // a way to remove horizontal scrollbar
		panelTable->HorizontalScroll->Maximum = 0;
		panelTable->AutoScroll = false;
		panelTable->VerticalScroll->Visible = false;
		panelTable->AutoScroll = true;
	}

	void SelectForm::GoBack() {
		this->Hide();
		menuForm->Show();
	}

	// BOTTOM FUNCTIONS

	System::Void SelectForm::buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
		GoBack();
	}

	System::Void SelectForm::buttonEntry_Click(System::Object^ sender, System::EventArgs^ e) {
		int hash = sender->GetHashCode();
		int gameId = (*btnHashes)[hash];
		playForm = gcnew PlayForm(this, gameId);
		this->Hide();
		playForm->Show();
	}

	System::Void SelectForm::SelectForm_VisibleChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->Visible) {
			Populate();

			if (playForm) {
				playForm->Close();
				playForm = nullptr;
			}
		}
		else {
			DeleteEntries();
		}
	}
}
