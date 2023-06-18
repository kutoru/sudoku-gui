#include "LoginForm.h"

namespace Sudoku {

	// TOP FUNCTIONS

	LoginForm::LoginForm(void) {
		InitializeComponent();

		LoadDb();
	}

	LoginForm::~LoginForm(void) {
		if (components) {
			delete components;
		}

		Application::Exit();
	}

	void LoginForm::LoadDb() {
		try {
			db.initialize();
		}
		catch (...) {
			buttonSubmit->Enabled = false;
			buttonCreate->Enabled = false;
			boxStatus->Text = L"Could not connect to the database";
		}
	}

	void LoginForm::OnSuccessfullLogin(Account a) {
		menuForm = gcnew MenuForm(this, a);
		this->Hide();
		menuForm->Show();
	}

	Account LoginForm::Login(System::String^ name, System::String^ pass) {
		Account a = Account::CheckPassword(conv(name), conv(pass));
		if (!a.wasFound) {
			boxStatus->Text = L"Username or password are wrong";
		}
		return a;
	}

	// BOTTOM FUNCTIONS

	System::Void LoginForm::LoginForm_VisibleChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->Visible) {
			if (newAccForm) {
				newAccForm->Close();
				newAccForm = nullptr;
			}
			else if (menuForm) {
				menuForm->Close();
				menuForm = nullptr;
			}
		}
	}

	System::Void LoginForm::buttonCreate_Click(System::Object^ sender, System::EventArgs^ e) {
		newAccForm = gcnew NewAccForm(this);
		this->Hide();
		newAccForm->Show();
	}

	System::Void LoginForm::buttonSubmit_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ name = boxLoginEnter->Text;
		System::String^ pass = boxPassEnter->Text;

		Account a = Login(name, pass);
		if (a.wasFound) {
			OnSuccessfullLogin(a);
		}
	}
}
