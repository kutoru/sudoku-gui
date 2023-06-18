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
		SelectForm(Form^ menuForm, int accId);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SelectForm();

	private:
		Form^ menuForm;
		int accId;
		System::Collections::Generic::List<Button^>^ buttons;
		std::unordered_map<int, int>* btnHashes;
		PlayForm^ playForm;

		Button^ CreateEntry(int btnIndex, int gameId, CompletedStatus completed, int size, char diff, std::string sdate);
		TextBox^ CreateStatus();
		void LoadBasicGameInfo();
		void GetRowInfo(int& gameId, CompletedStatus& completed, int& size, char& diff, std::string& sdate);
		void Populate();
		void DeleteEntries();
		void EnablePanelScroll();
		void GoBack();

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

	private: System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonEntry_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void SelectForm_VisibleChanged(System::Object^ sender, System::EventArgs^ e);

};
}
