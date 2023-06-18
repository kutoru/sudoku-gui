#include "LoginForm.h"

// https://stackoverflow.com/questions/7748137/is-it-possible-to-select-text-on-a-windows-form-label
// https://stackoverflow.com/questions/5768613/c-cli-how-to-open-a-new-form-and-back
// https://stackoverflow.com/questions/12607409/why-does-memory-usage-increase-with-each-click-to-the-button-in-windows-form-app
//
//

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(array<String^>^ args) {
	resetlog();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Sudoku::LoginForm loginForm;
	Application::Run(% loginForm);
}
