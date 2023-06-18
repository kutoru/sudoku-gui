#pragma once
#include "extra.h"

namespace Sudoku {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class NewAccForm : public System::Windows::Forms::Form {
	public:
		//char* availableChars = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~\0";

		NewAccForm(Form^ loginForm);

	protected:
		~NewAccForm();

	private:
		Form^ loginForm;

		void GoBack();
		bool IsValidCharacter(char ch);
		bool CheckLogin(System::String^ login);  // used for both username and password
		Account AddNewAccount(System::String^ name, System::String^ pass);

	private: System::Windows::Forms::Button^ buttonBack;
	private: System::Windows::Forms::TextBox^ boxStatus;
	private: System::Windows::Forms::Button^ buttonSubmit;
	private: System::Windows::Forms::TextBox^ boxPassEnter;
	private: System::Windows::Forms::TextBox^ boxLoginEnter;
	private: System::Windows::Forms::TextBox^ boxPass;
	private: System::Windows::Forms::TextBox^ boxLogin;
	private: System::Windows::Forms::TextBox^ boxInfo;
	private: System::Windows::Forms::TextBox^ boxReq;
	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonBack = (gcnew System::Windows::Forms::Button());
			this->boxReq = (gcnew System::Windows::Forms::TextBox());
			this->boxStatus = (gcnew System::Windows::Forms::TextBox());
			this->buttonSubmit = (gcnew System::Windows::Forms::Button());
			this->boxPassEnter = (gcnew System::Windows::Forms::TextBox());
			this->boxLoginEnter = (gcnew System::Windows::Forms::TextBox());
			this->boxPass = (gcnew System::Windows::Forms::TextBox());
			this->boxLogin = (gcnew System::Windows::Forms::TextBox());
			this->boxInfo = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// buttonBack
			// 
			this->buttonBack->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonBack->Location = System::Drawing::Point(14, 291);
			this->buttonBack->Name = L"buttonBack";
			this->buttonBack->Size = System::Drawing::Size(356, 29);
			this->buttonBack->TabIndex = 3;
			this->buttonBack->Text = L"Go back";
			this->buttonBack->UseVisualStyleBackColor = true;
			this->buttonBack->Click += gcnew System::EventHandler(this, &NewAccForm::buttonBack_Click);
			// 
			// boxReq
			// 
			this->boxReq->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxReq->Location = System::Drawing::Point(14, 46);
			this->boxReq->Margin = System::Windows::Forms::Padding(5);
			this->boxReq->Multiline = true;
			this->boxReq->Name = L"boxReq";
			this->boxReq->ReadOnly = true;
			this->boxReq->Size = System::Drawing::Size(356, 88);
			this->boxReq->TabIndex = 3;
			this->boxReq->TabStop = false;
			this->boxReq->Text = L"Both username and password must:\r\nhave lenght more than 3 and less than 21;\r\nonly"
				L" contain English uppercase and lowercase letters, as well as #$%&-_;";
			// 
			// boxStatus
			// 
			this->boxStatus->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxStatus->ForeColor = System::Drawing::Color::Crimson;
			this->boxStatus->Location = System::Drawing::Point(14, 144);
			this->boxStatus->Margin = System::Windows::Forms::Padding(5);
			this->boxStatus->Name = L"boxStatus";
			this->boxStatus->ReadOnly = true;
			this->boxStatus->Size = System::Drawing::Size(356, 22);
			this->boxStatus->TabIndex = 3;
			this->boxStatus->TabStop = false;
			this->boxStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// buttonSubmit
			// 
			this->buttonSubmit->Location = System::Drawing::Point(14, 254);
			this->buttonSubmit->Margin = System::Windows::Forms::Padding(5);
			this->buttonSubmit->Name = L"buttonSubmit";
			this->buttonSubmit->Size = System::Drawing::Size(356, 29);
			this->buttonSubmit->TabIndex = 2;
			this->buttonSubmit->Text = L"Submit";
			this->buttonSubmit->UseVisualStyleBackColor = true;
			this->buttonSubmit->Click += gcnew System::EventHandler(this, &NewAccForm::buttonSubmit_Click);
			// 
			// boxPassEnter
			// 
			this->boxPassEnter->Location = System::Drawing::Point(116, 215);
			this->boxPassEnter->Margin = System::Windows::Forms::Padding(5);
			this->boxPassEnter->Name = L"boxPassEnter";
			this->boxPassEnter->PasswordChar = '*';
			this->boxPassEnter->Size = System::Drawing::Size(254, 29);
			this->boxPassEnter->TabIndex = 1;
			// 
			// boxLoginEnter
			// 
			this->boxLoginEnter->Location = System::Drawing::Point(116, 176);
			this->boxLoginEnter->Margin = System::Windows::Forms::Padding(5);
			this->boxLoginEnter->Name = L"boxLoginEnter";
			this->boxLoginEnter->Size = System::Drawing::Size(254, 29);
			this->boxLoginEnter->TabIndex = 0;
			// 
			// boxPass
			// 
			this->boxPass->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxPass->Location = System::Drawing::Point(14, 218);
			this->boxPass->Margin = System::Windows::Forms::Padding(5);
			this->boxPass->Name = L"boxPass";
			this->boxPass->ReadOnly = true;
			this->boxPass->Size = System::Drawing::Size(216, 22);
			this->boxPass->TabIndex = 5;
			this->boxPass->TabStop = false;
			this->boxPass->Text = L"Password:";
			// 
			// boxLogin
			// 
			this->boxLogin->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxLogin->Location = System::Drawing::Point(14, 179);
			this->boxLogin->Margin = System::Windows::Forms::Padding(5);
			this->boxLogin->Name = L"boxLogin";
			this->boxLogin->ReadOnly = true;
			this->boxLogin->Size = System::Drawing::Size(216, 22);
			this->boxLogin->TabIndex = 6;
			this->boxLogin->TabStop = false;
			this->boxLogin->Text = L"Username:";
			// 
			// boxInfo
			// 
			this->boxInfo->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxInfo->Location = System::Drawing::Point(14, 14);
			this->boxInfo->Margin = System::Windows::Forms::Padding(5);
			this->boxInfo->Name = L"boxInfo";
			this->boxInfo->ReadOnly = true;
			this->boxInfo->Size = System::Drawing::Size(356, 22);
			this->boxInfo->TabIndex = 10;
			this->boxInfo->TabStop = false;
			this->boxInfo->Text = L"Enter new username and password";
			this->boxInfo->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// NewAccForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(384, 336);
			this->Controls->Add(this->boxInfo);
			this->Controls->Add(this->buttonSubmit);
			this->Controls->Add(this->boxPassEnter);
			this->Controls->Add(this->boxLoginEnter);
			this->Controls->Add(this->boxPass);
			this->Controls->Add(this->boxLogin);
			this->Controls->Add(this->boxStatus);
			this->Controls->Add(this->boxReq);
			this->Controls->Add(this->buttonBack);
			this->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"NewAccForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sudoku | Create new Account";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonSubmit_Click(System::Object^ sender, System::EventArgs^ e);

};
}
