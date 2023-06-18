#pragma once
#include "extra.h"

public ref class TextBoxM : public System::Windows::Forms::TextBox {
public:
	int tRow;  // table row and col
	int tCol;
	bool replaceable;
	System::String^ prevChar;

	TextBoxM(int row, int col, char ch, bool replaceable) : TextBox() {
		this->tRow = row;
		this->tCol = col;
		this->replaceable = replaceable;

		if (ch) {
			this->Text = conv(ch);
		}
		else {
			this->Text = "";
		}

		this->prevChar = this->Text;
	}
};
