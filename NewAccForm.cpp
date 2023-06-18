#include "NewAccForm.h"

namespace Sudoku {
	// TOP FUNCTIONS

	NewAccForm::NewAccForm(Form^ loginForm) {
		InitializeComponent();

		this->loginForm = loginForm;
	}

	NewAccForm::~NewAccForm() {
		if (this->Visible) {
			GoBack();
		}

		if (components) {
			delete components;
		}
	}

	void NewAccForm::GoBack() {
		this->Hide();
		loginForm->Show();
	}

	bool NewAccForm::IsValidCharacter(char ch) {
		char ach;
		for (int i = 0; AVAL_CHARS[i]; i++) {
			ach = AVAL_CHARS[i];
			if (ch == ach) {
				return true;
			}
		}

		return false;
	}

	bool NewAccForm::CheckLogin(System::String^ login) {  // used for both username and password
		if (login->Length < 4 || login->Length > 20) {
			return false;
		}

		char ch;
		for (int i = 0; i < login->Length; i++) {
			ch = login[i];
			if (!IsValidCharacter(ch)) {
				return false;
			}
		}

		return true;
	}

	Account NewAccForm::AddNewAccount(System::String^ name, System::String^ pass) {
		Account a;

		if (!CheckLogin(name)) {
			boxStatus->Text = L"Invalid username";
			return a;
		}
		if (!CheckLogin(pass)) {
			boxStatus->Text = L"Invalid password";
			return a;
		}

		//connect to the db and try to set name and pass
		bool nameAvailable = Account::CheckNameAvailability(conv(name));
		if (!nameAvailable) {
			boxStatus->Text = L"The username already exists";
			return a;
		}

		try {
			return Account::CreateNew(conv(name), conv(pass));
		}
		catch (exep& e) {
			logl(e.msg, true);
			boxStatus->Text = L"Something went wrong when creating the Account";
			return a;
		}
	}

	// BOTTOM FUNCTIONS

	System::Void NewAccForm::buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
		GoBack();
	}

	System::Void NewAccForm::buttonSubmit_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ name = boxLoginEnter->Text;
		System::String^ pass = boxPassEnter->Text;

		Account a = AddNewAccount(name, pass);
		if (a.wasFound) {
			boxStatus->Text = L"Account has been created, go back and log in";
		}
	}
}
