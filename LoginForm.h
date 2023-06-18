#pragma once
#include "MenuForm.h"
#include "NewAccForm.h"

namespace Sudoku {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class LoginForm : public System::Windows::Forms::Form {
	public:
		LoginForm(void);

	protected:
		~LoginForm();

		//void OnShown(System::EventArgs^ e) override {
		//	__super::OnShown(e);
		//}

	private:
		NewAccForm^ newAccForm = nullptr;
		MenuForm^ menuForm = nullptr;

		void LoadDb();
		void OnSuccessfullLogin(Account a);
		Account Login(System::String^ name, System::String^ pass);

	private: System::Windows::Forms::TextBox^ boxInfo;
	private: System::Windows::Forms::TextBox^ boxLoginEnter;
	private: System::Windows::Forms::TextBox^ boxPassEnter;
	private: System::Windows::Forms::TextBox^ boxLogin;
	private: System::Windows::Forms::TextBox^ boxPass;
	private: System::Windows::Forms::Button^ buttonSubmit;
	private: System::Windows::Forms::Button^ buttonCreate;
	private: System::Windows::Forms::TextBox^ boxStatus;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->boxInfo = (gcnew System::Windows::Forms::TextBox());
			this->boxLoginEnter = (gcnew System::Windows::Forms::TextBox());
			this->boxPassEnter = (gcnew System::Windows::Forms::TextBox());
			this->boxLogin = (gcnew System::Windows::Forms::TextBox());
			this->boxPass = (gcnew System::Windows::Forms::TextBox());
			this->buttonSubmit = (gcnew System::Windows::Forms::Button());
			this->buttonCreate = (gcnew System::Windows::Forms::Button());
			this->boxStatus = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// boxInfo
			// 
			this->boxInfo->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxInfo->ForeColor = System::Drawing::SystemColors::WindowText;
			this->boxInfo->Location = System::Drawing::Point(14, 14);
			this->boxInfo->Margin = System::Windows::Forms::Padding(5);
			this->boxInfo->Name = L"boxInfo";
			this->boxInfo->ReadOnly = true;
			this->boxInfo->Size = System::Drawing::Size(356, 22);
			this->boxInfo->TabIndex = 7;
			this->boxInfo->TabStop = false;
			this->boxInfo->Text = L"Enter your username and password";
			this->boxInfo->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// boxLoginEnter
			// 
			this->boxLoginEnter->Location = System::Drawing::Point(116, 78);
			this->boxLoginEnter->Margin = System::Windows::Forms::Padding(5);
			this->boxLoginEnter->Name = L"boxLoginEnter";
			this->boxLoginEnter->Size = System::Drawing::Size(254, 29);
			this->boxLoginEnter->TabIndex = 0;
			// 
			// boxPassEnter
			// 
			this->boxPassEnter->Location = System::Drawing::Point(116, 117);
			this->boxPassEnter->Margin = System::Windows::Forms::Padding(5);
			this->boxPassEnter->Name = L"boxPassEnter";
			this->boxPassEnter->PasswordChar = '*';
			this->boxPassEnter->Size = System::Drawing::Size(254, 29);
			this->boxPassEnter->TabIndex = 1;
			// 
			// boxLogin
			// 
			this->boxLogin->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxLogin->Location = System::Drawing::Point(14, 81);
			this->boxLogin->Margin = System::Windows::Forms::Padding(5);
			this->boxLogin->Name = L"boxLogin";
			this->boxLogin->ReadOnly = true;
			this->boxLogin->Size = System::Drawing::Size(216, 22);
			this->boxLogin->TabIndex = 5;
			this->boxLogin->TabStop = false;
			this->boxLogin->Text = L"Username:";
			// 
			// boxPass
			// 
			this->boxPass->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxPass->Location = System::Drawing::Point(14, 120);
			this->boxPass->Margin = System::Windows::Forms::Padding(5);
			this->boxPass->Name = L"boxPass";
			this->boxPass->ReadOnly = true;
			this->boxPass->Size = System::Drawing::Size(216, 22);
			this->boxPass->TabIndex = 4;
			this->boxPass->TabStop = false;
			this->boxPass->Text = L"Password:";
			// 
			// buttonSubmit
			// 
			this->buttonSubmit->Location = System::Drawing::Point(14, 156);
			this->buttonSubmit->Margin = System::Windows::Forms::Padding(5);
			this->buttonSubmit->Name = L"buttonSubmit";
			this->buttonSubmit->Size = System::Drawing::Size(356, 29);
			this->buttonSubmit->TabIndex = 2;
			this->buttonSubmit->Text = L"Submit";
			this->buttonSubmit->UseVisualStyleBackColor = true;
			this->buttonSubmit->Click += gcnew System::EventHandler(this, &LoginForm::buttonSubmit_Click);
			// 
			// buttonCreate
			// 
			this->buttonCreate->Location = System::Drawing::Point(14, 195);
			this->buttonCreate->Margin = System::Windows::Forms::Padding(5);
			this->buttonCreate->Name = L"buttonCreate";
			this->buttonCreate->Size = System::Drawing::Size(356, 29);
			this->buttonCreate->TabIndex = 3;
			this->buttonCreate->Text = L"Create a new Account";
			this->buttonCreate->UseVisualStyleBackColor = true;
			this->buttonCreate->Click += gcnew System::EventHandler(this, &LoginForm::buttonCreate_Click);
			// 
			// boxStatus
			// 
			this->boxStatus->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxStatus->ForeColor = System::Drawing::Color::Crimson;
			this->boxStatus->Location = System::Drawing::Point(14, 46);
			this->boxStatus->Margin = System::Windows::Forms::Padding(5);
			this->boxStatus->Name = L"boxStatus";
			this->boxStatus->ReadOnly = true;
			this->boxStatus->Size = System::Drawing::Size(356, 22);
			this->boxStatus->TabIndex = 6;
			this->boxStatus->TabStop = false;
			this->boxStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// LoginForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(384, 236);
			this->Controls->Add(this->buttonCreate);
			this->Controls->Add(this->buttonSubmit);
			this->Controls->Add(this->boxPassEnter);
			this->Controls->Add(this->boxLoginEnter);
			this->Controls->Add(this->boxPass);
			this->Controls->Add(this->boxLogin);
			this->Controls->Add(this->boxStatus);
			this->Controls->Add(this->boxInfo);
			this->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"LoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sudoku | Login";
			this->VisibleChanged += gcnew System::EventHandler(this, &LoginForm::LoginForm_VisibleChanged);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void LoginForm_VisibleChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonCreate_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonSubmit_Click(System::Object^ sender, System::EventArgs^ e);

};
}
