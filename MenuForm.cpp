#include "MenuForm.h"

namespace Sudoku {
	// TOP FUNCTIONS

	MenuForm::MenuForm(System::Windows::Forms::Form^ loginForm, Account& a) {
		InitializeComponent();

		this->loginForm = loginForm;
		acc = new Account(a);
		newGameForm = nullptr;
		selectForm = nullptr;
	}

	MenuForm::~MenuForm() {
		if (this->Visible) {
			GoBack();
		}

		if (components) {
			delete components;
		}
	}

	void MenuForm::LoadInfo() {
		boxAccId->Text = L"ID: " + acc->id;
		boxAccName->Text = L"Name: " + conv(acc->username);
		boxAccDate->Text = L"Account created on: " + conv(acc->dateCreated.to_string());
		boxTotalGames->Text = L"Total games: " + Account::GetTotalGameCount(acc->id);
		boxCompletedGames->Text = L"Completed games: " + Account::GetCompletedGameCount(acc->id);
	}

	void MenuForm::GoBack() {
		this->Hide();
		loginForm->Show();
	}

	// BOTTOM FUNCTIONS

	System::Void MenuForm::buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
		GoBack();
	}

	System::Void MenuForm::buttonNewGame_Click(System::Object^ sender, System::EventArgs^ e) {
		newGameForm = gcnew NewGameForm(this, acc->id);
		this->Hide();
		newGameForm->Show();
	}

	System::Void MenuForm::buttonSelect_Click(System::Object^ sender, System::EventArgs^ e) {
		selectForm = gcnew SelectForm(this, acc->id);
		this->Hide();
		selectForm->Show();
	}

	System::Void MenuForm::MenuForm_VisibleChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->Visible) {
			LoadInfo();

			if (newGameForm) {
				newGameForm->Close();
				newGameForm = nullptr;
			}

			else if (selectForm) {
				selectForm->Close();
				selectForm = nullptr;
			}
		}
	}
}
