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
		PlayForm(Form^ selectForm, int gameId);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlayForm();

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

		void LoadGameObject();
		void LoadVars();
		void ResizeForm();
		System::String^ FormatDiff();
		System::String^ FormatDate();
		System::String^ FormatAvalChars(int sqrSize);
		void ChangeInfo();
		void MoveButtons();
		void CreateTable();
		TextBox^ CreateCell(int i, int j);
		void FillTable();
		void AddLine(int x, int y, int w, int h);
		void AddLines();
		void LoadUI();
		void OnError();
		System::String^ ValidateText(TextBoxM^ textBox);
		bool IsInSquare(TextBoxM^ tb, int sqrIdx);
		void StopTimer();
		void LightDown(TextBoxM^ tb);
		void LightUp(Validation vld);
		int GetNewColor(int startColor, int endColor, int progress);
		void MoveSelectionToEnd(TextBoxM^ tb);
		void OnLevelCompleted(CompletedStatus compStatus);
		void CancelCurrAction(bool updateStatus, bool shiftFocusBack);
		void AskForConfirmation(ActType action);
		void ResetTable();
		void GiveUp();
		bool DeleteGame();
		void DeleteVals();
		void GoBack();

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

	private: System::Void cell_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonValidate_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void TimerTick(Object^ sender, EventArgs^ e);
	private: System::Void cell_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonConfirm_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonReset_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonGiveup_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonDelete_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonCancel_Click(System::Object^ sender, System::EventArgs^ e);

};
}
