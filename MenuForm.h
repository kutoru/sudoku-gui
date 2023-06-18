#pragma once
#include "extra.h"
#include "NewGameForm.h"
#include "SelectForm.h"

namespace Sudoku {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MenuForm : public System::Windows::Forms::Form {
	public:
		MenuForm(System::Windows::Forms::Form^ loginForm, Account& a);

	protected:
		~MenuForm();

	private:
		System::Windows::Forms::Form^ loginForm;
		Account* acc;
		NewGameForm^ newGameForm;
		SelectForm^ selectForm;

		void LoadInfo();
		void GoBack();

	private: System::Windows::Forms::TextBox^ boxTotalGames;
	private: System::Windows::Forms::TextBox^ boxCompletedGames;
	private: System::Windows::Forms::Button^ buttonSelect;
	private: System::Windows::Forms::TextBox^ boxAccName;
	private: System::Windows::Forms::TextBox^ boxAccDate;
	private: System::Windows::Forms::Button^ buttonNewGame;
	private: System::Windows::Forms::TextBox^ boxStatus;
	private: System::Windows::Forms::Button^ buttonBack;
	private: System::Windows::Forms::TextBox^ boxAccId;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonBack = (gcnew System::Windows::Forms::Button());
			this->boxAccId = (gcnew System::Windows::Forms::TextBox());
			this->boxAccName = (gcnew System::Windows::Forms::TextBox());
			this->boxAccDate = (gcnew System::Windows::Forms::TextBox());
			this->buttonNewGame = (gcnew System::Windows::Forms::Button());
			this->boxStatus = (gcnew System::Windows::Forms::TextBox());
			this->boxTotalGames = (gcnew System::Windows::Forms::TextBox());
			this->boxCompletedGames = (gcnew System::Windows::Forms::TextBox());
			this->buttonSelect = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonBack
			// 
			this->buttonBack->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonBack->Location = System::Drawing::Point(13, 209);
			this->buttonBack->Margin = System::Windows::Forms::Padding(4);
			this->buttonBack->Name = L"buttonBack";
			this->buttonBack->Size = System::Drawing::Size(358, 30);
			this->buttonBack->TabIndex = 3;
			this->buttonBack->Text = L"Go back";
			this->buttonBack->UseVisualStyleBackColor = true;
			this->buttonBack->Click += gcnew System::EventHandler(this, &MenuForm::buttonBack_Click);
			// 
			// boxAccId
			// 
			this->boxAccId->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxAccId->Location = System::Drawing::Point(275, 13);
			this->boxAccId->Margin = System::Windows::Forms::Padding(4);
			this->boxAccId->Name = L"boxAccId";
			this->boxAccId->ReadOnly = true;
			this->boxAccId->Size = System::Drawing::Size(96, 22);
			this->boxAccId->TabIndex = 2;
			this->boxAccId->TabStop = false;
			this->boxAccId->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// boxAccName
			// 
			this->boxAccName->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxAccName->Location = System::Drawing::Point(13, 13);
			this->boxAccName->Margin = System::Windows::Forms::Padding(4);
			this->boxAccName->Name = L"boxAccName";
			this->boxAccName->ReadOnly = true;
			this->boxAccName->Size = System::Drawing::Size(254, 22);
			this->boxAccName->TabIndex = 2;
			this->boxAccName->TabStop = false;
			// 
			// boxAccDate
			// 
			this->boxAccDate->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxAccDate->Location = System::Drawing::Point(13, 43);
			this->boxAccDate->Margin = System::Windows::Forms::Padding(4);
			this->boxAccDate->Name = L"boxAccDate";
			this->boxAccDate->ReadOnly = true;
			this->boxAccDate->Size = System::Drawing::Size(358, 22);
			this->boxAccDate->TabIndex = 2;
			this->boxAccDate->TabStop = false;
			// 
			// buttonNewGame
			// 
			this->buttonNewGame->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonNewGame->Location = System::Drawing::Point(13, 133);
			this->buttonNewGame->Margin = System::Windows::Forms::Padding(4);
			this->buttonNewGame->Name = L"buttonNewGame";
			this->buttonNewGame->Size = System::Drawing::Size(358, 30);
			this->buttonNewGame->TabIndex = 1;
			this->buttonNewGame->Text = L"Create new game";
			this->buttonNewGame->UseVisualStyleBackColor = true;
			this->buttonNewGame->Click += gcnew System::EventHandler(this, &MenuForm::buttonNewGame_Click);
			// 
			// boxStatus
			// 
			this->boxStatus->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxStatus->Location = System::Drawing::Point(13, 103);
			this->boxStatus->Margin = System::Windows::Forms::Padding(4);
			this->boxStatus->Name = L"boxStatus";
			this->boxStatus->ReadOnly = true;
			this->boxStatus->Size = System::Drawing::Size(358, 22);
			this->boxStatus->TabIndex = 2;
			this->boxStatus->TabStop = false;
			this->boxStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// boxTotalGames
			// 
			this->boxTotalGames->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxTotalGames->Location = System::Drawing::Point(13, 73);
			this->boxTotalGames->Margin = System::Windows::Forms::Padding(4);
			this->boxTotalGames->Name = L"boxTotalGames";
			this->boxTotalGames->ReadOnly = true;
			this->boxTotalGames->Size = System::Drawing::Size(175, 22);
			this->boxTotalGames->TabIndex = 2;
			this->boxTotalGames->TabStop = false;
			// 
			// boxCompletedGames
			// 
			this->boxCompletedGames->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxCompletedGames->Location = System::Drawing::Point(196, 73);
			this->boxCompletedGames->Margin = System::Windows::Forms::Padding(4);
			this->boxCompletedGames->Name = L"boxCompletedGames";
			this->boxCompletedGames->ReadOnly = true;
			this->boxCompletedGames->Size = System::Drawing::Size(175, 22);
			this->boxCompletedGames->TabIndex = 2;
			this->boxCompletedGames->TabStop = false;
			// 
			// buttonSelect
			// 
			this->buttonSelect->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonSelect->Location = System::Drawing::Point(13, 171);
			this->buttonSelect->Margin = System::Windows::Forms::Padding(4);
			this->buttonSelect->Name = L"buttonSelect";
			this->buttonSelect->Size = System::Drawing::Size(358, 30);
			this->buttonSelect->TabIndex = 2;
			this->buttonSelect->Text = L"Select a game";
			this->buttonSelect->UseVisualStyleBackColor = true;
			this->buttonSelect->Click += gcnew System::EventHandler(this, &MenuForm::buttonSelect_Click);
			// 
			// MenuForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(384, 246);
			this->Controls->Add(this->buttonSelect);
			this->Controls->Add(this->buttonNewGame);
			this->Controls->Add(this->buttonBack);
			this->Controls->Add(this->boxCompletedGames);
			this->Controls->Add(this->boxTotalGames);
			this->Controls->Add(this->boxStatus);
			this->Controls->Add(this->boxAccDate);
			this->Controls->Add(this->boxAccName);
			this->Controls->Add(this->boxAccId);
			this->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"MenuForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sudoku | Menu";
			this->VisibleChanged += gcnew System::EventHandler(this, &MenuForm::MenuForm_VisibleChanged);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonNewGame_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonSelect_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MenuForm_VisibleChanged(System::Object^ sender, System::EventArgs^ e);

};
}
