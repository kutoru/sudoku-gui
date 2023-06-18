#pragma once
#include "extra.h"
#include "PlayForm.h"
#include <unordered_map>

namespace Sudoku {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SelectForm
	/// </summary>
	public ref class SelectForm : public System::Windows::Forms::Form
	{
	public:
		SelectForm(Form^ menuForm, int accId) {
			InitializeComponent();

			this->menuForm = menuForm;
			this->accId = accId;
			this->playForm = nullptr;
			this->buttons = nullptr;
			this->btnHashes = nullptr;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SelectForm() {
			if (this->Visible) {
				GoBack();
			}

			DeleteEntries();

			if (components) {
				delete components;
			}
		}

	private:
		Form^ menuForm;
		int accId;
		System::Collections::Generic::List<Button^>^ buttons;
		std::unordered_map<int, int>* btnHashes;
		PlayForm^ playForm;

		Button^ CreateEntry(int btnIndex, int gameId, CompletedStatus completed, int size, char diff, std::string sdate) {  // future arguments will be: gameId, completion, size, etc
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

		TextBox^ CreateStatus() {
			TextBox^ boxStatus = gcnew TextBox();

			boxStatus->BorderStyle = System::Windows::Forms::BorderStyle::None;
			boxStatus->ReadOnly = true;
			boxStatus->Size = System::Drawing::Size(352, 47);
			boxStatus->TabStop = false;
			boxStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			boxStatus->Text = L"No games were found. Go back and create some";

			return boxStatus;
		}

		void LoadBasicGameInfo() {
			db.query << "select `id`, `completed`, `size`, `difficulty`, `date_created` from games where user_id = " << accId << " order by `id` desc;";
			db.load_res();
		}

		void GetRowInfo(int& gameId, CompletedStatus& completed, int& size, char& diff, std::string& sdate) {
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

		void Populate() {
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

		void DeleteEntries() {
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

		void EnablePanelScroll() {  // a way to remove horizontal scrollbar
			panelTable->HorizontalScroll->Maximum = 0;
			panelTable->AutoScroll = false;
			panelTable->VerticalScroll->Visible = false;
			panelTable->AutoScroll = true;
		}

		void GoBack() {
			this->Hide();
			menuForm->Show();
		}

	private: System::Windows::Forms::TableLayoutPanel^ panelTable;
	private: System::Windows::Forms::Button^ buttonBack;
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
			this->panelTable = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->SuspendLayout();
			// 
			// buttonBack
			// 
			this->buttonBack->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonBack->Location = System::Drawing::Point(13, 418);
			this->buttonBack->Margin = System::Windows::Forms::Padding(4);
			this->buttonBack->Name = L"buttonBack";
			this->buttonBack->Size = System::Drawing::Size(358, 30);
			this->buttonBack->TabIndex = 4;
			this->buttonBack->Text = L"Go back";
			this->buttonBack->UseVisualStyleBackColor = true;
			this->buttonBack->Click += gcnew System::EventHandler(this, &SelectForm::buttonBack_Click);
			// 
			// panelTable
			// 
			this->panelTable->ColumnCount = 1;
			this->panelTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->panelTable->Location = System::Drawing::Point(13, 12);
			this->panelTable->Name = L"panelTable";
			this->panelTable->RowCount = 1;
			this->panelTable->Size = System::Drawing::Size(358, 399);
			this->panelTable->TabIndex = 5;
			// 
			// SelectForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(384, 461);
			this->Controls->Add(this->panelTable);
			this->Controls->Add(this->buttonBack);
			this->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"SelectForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sudoku | Select a game";
			this->VisibleChanged += gcnew System::EventHandler(this, &SelectForm::SelectForm_VisibleChanged);
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
	GoBack();
}

private: System::Void buttonEntry_Click(System::Object^ sender, System::EventArgs^ e) {
	int hash = sender->GetHashCode();
	int gameId = (*btnHashes)[hash];
	playForm = gcnew PlayForm(this, gameId);
	this->Hide();
	playForm->Show();
}

private: System::Void SelectForm_VisibleChanged(System::Object^ sender, System::EventArgs^ e) {
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

};
}
