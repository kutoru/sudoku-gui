#pragma once
#include "extra.h"

namespace Sudoku {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NewGameForm
	/// </summary>
	public ref class NewGameForm : public System::Windows::Forms::Form
	{
	public:
		NewGameForm(Form^ menuForm, int accId);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NewGameForm();

	private:
		Form^ menuForm;
		int accId;
		int size;
		Difficulty diff;
		BackgroundWorker^ bgWorker;
		Game* game;
		bool stopFromClosing;

		void InitializeBGWorker();
		void CreateNewGame(int s, Difficulty d, BackgroundWorker^ w, DoWorkEventArgs^ e);
		void GoBack();

	private: System::Windows::Forms::Button^ buttonCancel;
	private: System::Windows::Forms::Button^ buttonBack;
	private: System::Windows::Forms::TextBox^ boxStatus;
	private: System::Windows::Forms::Button^ buttonCreate;
	private: System::Windows::Forms::Button^ buttonSize4;
	private: System::Windows::Forms::TextBox^ boxSize;
	private: System::Windows::Forms::TextBox^ boxDifficulty;
	private: System::Windows::Forms::Button^ buttonSize9;
	private: System::Windows::Forms::Button^ buttonSize16;
	private: System::Windows::Forms::Button^ buttonDiffHard;
	private: System::Windows::Forms::Button^ buttonDiffMedi;
	private: System::Windows::Forms::Button^ buttonDiffEasy;

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
			this->buttonCreate = (gcnew System::Windows::Forms::Button());
			this->buttonSize4 = (gcnew System::Windows::Forms::Button());
			this->boxSize = (gcnew System::Windows::Forms::TextBox());
			this->boxDifficulty = (gcnew System::Windows::Forms::TextBox());
			this->buttonSize9 = (gcnew System::Windows::Forms::Button());
			this->buttonSize16 = (gcnew System::Windows::Forms::Button());
			this->buttonDiffHard = (gcnew System::Windows::Forms::Button());
			this->buttonDiffMedi = (gcnew System::Windows::Forms::Button());
			this->buttonDiffEasy = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonBack
			// 
			this->buttonBack->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonBack->Location = System::Drawing::Point(13, 149);
			this->buttonBack->Margin = System::Windows::Forms::Padding(4);
			this->buttonBack->Name = L"buttonBack";
			this->buttonBack->Size = System::Drawing::Size(358, 30);
			this->buttonBack->TabIndex = 8;
			this->buttonBack->Text = L"Go back";
			this->buttonBack->UseVisualStyleBackColor = true;
			this->buttonBack->Click += gcnew System::EventHandler(this, &NewGameForm::buttonBack_Click);
			// 
			// boxStatus
			// 
			this->boxStatus->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxStatus->Location = System::Drawing::Point(13, 81);
			this->boxStatus->Margin = System::Windows::Forms::Padding(4);
			this->boxStatus->Name = L"boxStatus";
			this->boxStatus->ReadOnly = true;
			this->boxStatus->Size = System::Drawing::Size(358, 22);
			this->boxStatus->TabIndex = 5;
			this->boxStatus->TabStop = false;
			this->boxStatus->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// buttonCreate
			// 
			this->buttonCreate->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonCreate->Location = System::Drawing::Point(13, 111);
			this->buttonCreate->Margin = System::Windows::Forms::Padding(4);
			this->buttonCreate->Name = L"buttonCreate";
			this->buttonCreate->Size = System::Drawing::Size(358, 30);
			this->buttonCreate->TabIndex = 7;
			this->buttonCreate->Text = L"Create";
			this->buttonCreate->UseVisualStyleBackColor = true;
			this->buttonCreate->Click += gcnew System::EventHandler(this, &NewGameForm::buttonCreate_Click);
			// 
			// buttonSize4
			// 
			this->buttonSize4->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonSize4->Location = System::Drawing::Point(13, 43);
			this->buttonSize4->Margin = System::Windows::Forms::Padding(4);
			this->buttonSize4->Name = L"buttonSize4";
			this->buttonSize4->Size = System::Drawing::Size(53, 30);
			this->buttonSize4->TabIndex = 1;
			this->buttonSize4->Text = L"4";
			this->buttonSize4->UseVisualStyleBackColor = true;
			this->buttonSize4->Click += gcnew System::EventHandler(this, &NewGameForm::buttonSize4_Click);
			// 
			// boxSize
			// 
			this->boxSize->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxSize->Location = System::Drawing::Point(13, 13);
			this->boxSize->Margin = System::Windows::Forms::Padding(4);
			this->boxSize->Name = L"boxSize";
			this->boxSize->ReadOnly = true;
			this->boxSize->Size = System::Drawing::Size(175, 22);
			this->boxSize->TabIndex = 6;
			this->boxSize->TabStop = false;
			this->boxSize->Text = L"Selected size:";
			// 
			// boxDifficulty
			// 
			this->boxDifficulty->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->boxDifficulty->Location = System::Drawing::Point(196, 13);
			this->boxDifficulty->Margin = System::Windows::Forms::Padding(4);
			this->boxDifficulty->Name = L"boxDifficulty";
			this->boxDifficulty->ReadOnly = true;
			this->boxDifficulty->Size = System::Drawing::Size(175, 22);
			this->boxDifficulty->TabIndex = 7;
			this->boxDifficulty->TabStop = false;
			this->boxDifficulty->Text = L"Selected difficulty:";
			// 
			// buttonSize9
			// 
			this->buttonSize9->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonSize9->Location = System::Drawing::Point(74, 43);
			this->buttonSize9->Margin = System::Windows::Forms::Padding(4);
			this->buttonSize9->Name = L"buttonSize9";
			this->buttonSize9->Size = System::Drawing::Size(53, 30);
			this->buttonSize9->TabIndex = 2;
			this->buttonSize9->Text = L"9";
			this->buttonSize9->UseVisualStyleBackColor = true;
			this->buttonSize9->Click += gcnew System::EventHandler(this, &NewGameForm::buttonSize9_Click);
			// 
			// buttonSize16
			// 
			this->buttonSize16->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonSize16->Location = System::Drawing::Point(135, 43);
			this->buttonSize16->Margin = System::Windows::Forms::Padding(4);
			this->buttonSize16->Name = L"buttonSize16";
			this->buttonSize16->Size = System::Drawing::Size(53, 30);
			this->buttonSize16->TabIndex = 3;
			this->buttonSize16->Text = L"16";
			this->buttonSize16->UseVisualStyleBackColor = true;
			this->buttonSize16->Click += gcnew System::EventHandler(this, &NewGameForm::buttonSize16_Click);
			// 
			// buttonDiffHard
			// 
			this->buttonDiffHard->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonDiffHard->Location = System::Drawing::Point(318, 43);
			this->buttonDiffHard->Margin = System::Windows::Forms::Padding(4);
			this->buttonDiffHard->Name = L"buttonDiffHard";
			this->buttonDiffHard->Size = System::Drawing::Size(53, 30);
			this->buttonDiffHard->TabIndex = 6;
			this->buttonDiffHard->Text = L"Hard";
			this->buttonDiffHard->UseVisualStyleBackColor = true;
			this->buttonDiffHard->Click += gcnew System::EventHandler(this, &NewGameForm::buttonDiffHard_Click);
			// 
			// buttonDiffMedi
			// 
			this->buttonDiffMedi->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonDiffMedi->Location = System::Drawing::Point(257, 43);
			this->buttonDiffMedi->Margin = System::Windows::Forms::Padding(4);
			this->buttonDiffMedi->Name = L"buttonDiffMedi";
			this->buttonDiffMedi->Size = System::Drawing::Size(53, 30);
			this->buttonDiffMedi->TabIndex = 5;
			this->buttonDiffMedi->Text = L"Medi";
			this->buttonDiffMedi->UseVisualStyleBackColor = true;
			this->buttonDiffMedi->Click += gcnew System::EventHandler(this, &NewGameForm::buttonDiffMedi_Click);
			// 
			// buttonDiffEasy
			// 
			this->buttonDiffEasy->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonDiffEasy->Location = System::Drawing::Point(196, 43);
			this->buttonDiffEasy->Margin = System::Windows::Forms::Padding(4);
			this->buttonDiffEasy->Name = L"buttonDiffEasy";
			this->buttonDiffEasy->Size = System::Drawing::Size(53, 30);
			this->buttonDiffEasy->TabIndex = 4;
			this->buttonDiffEasy->Text = L"Easy";
			this->buttonDiffEasy->UseVisualStyleBackColor = true;
			this->buttonDiffEasy->Click += gcnew System::EventHandler(this, &NewGameForm::buttonDiffEasy_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Enabled = false;
			this->buttonCancel->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonCancel->Location = System::Drawing::Point(13, 149);
			this->buttonCancel->Margin = System::Windows::Forms::Padding(4);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(358, 30);
			this->buttonCancel->TabIndex = 8;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &NewGameForm::buttonCancel_Click);
			// 
			// NewGameForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(384, 186);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonDiffHard);
			this->Controls->Add(this->buttonDiffMedi);
			this->Controls->Add(this->buttonDiffEasy);
			this->Controls->Add(this->boxDifficulty);
			this->Controls->Add(this->boxSize);
			this->Controls->Add(this->boxStatus);
			this->Controls->Add(this->buttonSize16);
			this->Controls->Add(this->buttonSize9);
			this->Controls->Add(this->buttonSize4);
			this->Controls->Add(this->buttonCreate);
			this->Controls->Add(this->buttonBack);
			this->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"NewGameForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sudoku | Create new game";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &NewGameForm::NewGameForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void buttonCancel_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonCreate_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void buttonSize4_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonSize9_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonSize16_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonDiffEasy_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonDiffMedi_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonDiffHard_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void OnDoWork(System::Object^ sender, DoWorkEventArgs^ e);
	private: System::Void OnWorkerCompleted(System::Object^ sender, RunWorkerCompletedEventArgs^ e);
	private: System::Void NewGameForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);

};
}
