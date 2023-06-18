#include "NewGameForm.h"

namespace Sudoku {
	// TOP FUNCTIONS

	NewGameForm::NewGameForm(Form^ menuForm, int accId) {
		InitializeComponent();

		this->menuForm = menuForm;
		this->accId = accId;
		size = 0;
		diff = Difficulty::None;

		// https://stackoverflow.com/questions/259676/stopping-a-function-executed-on-a-winform-button-click
		//                                            VVV
		// https://learn.microsoft.com/en-us/dotnet/api/system.componentmodel.backgroundworker?redirectedfrom=MSDN&view=net-7.0

		bgWorker = nullptr;
		game = nullptr;
		stopFromClosing = false;
		buttonCancel->Hide();

		InitializeBGWorker();
	}

	NewGameForm::~NewGameForm() {
		if (this->Visible) {
			GoBack();
		}

		if (components) {
			delete components;
		}
	}

	void NewGameForm::InitializeBGWorker() {
		bgWorker = gcnew BackgroundWorker();
		bgWorker->WorkerSupportsCancellation = true;
		bgWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Sudoku::NewGameForm::OnDoWork);
		bgWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Sudoku::NewGameForm::OnWorkerCompleted);
	}

	void NewGameForm::CreateNewGame(int s, Difficulty d, BackgroundWorker^ w, DoWorkEventArgs^ e) {
		game = new Game(s, d, accId);
		game->GenerateNewBoard(w, e);
		game->GenerateLevel();
	}

	void NewGameForm::GoBack() {
		this->Hide();
		menuForm->Show();
	}

	// BOTTOM FUNCTIONS

	System::Void NewGameForm::buttonCancel_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!bgWorker->CancellationPending) {
			bgWorker->CancelAsync();
		}
	}

	System::Void NewGameForm::buttonBack_Click(System::Object^ sender, System::EventArgs^ e) {
		GoBack();
	}

	System::Void NewGameForm::buttonCreate_Click(System::Object^ sender, System::EventArgs^ e) {
		if (size == 0 || diff == Difficulty::None) {
			boxStatus->Text = L"Select size and difficulty first";
			return;
		}

		boxStatus->Text = L"Generating a new level...";
		buttonCreate->Enabled = false;
		stopFromClosing = true;

		buttonBack->Enabled = false;
		buttonBack->Hide();

		buttonCancel->Enabled = true;
		buttonCancel->Show();
		buttonCancel->Focus();

		bgWorker->RunWorkerAsync();
	}

	System::Void NewGameForm::buttonSize4_Click(System::Object^ sender, System::EventArgs^ e) {
		size = 4;
		boxSize->Text = L"Selected size: 4x4";
	}
	System::Void NewGameForm::buttonSize9_Click(System::Object^ sender, System::EventArgs^ e) {
		size = 9;
		boxSize->Text = L"Selected size: 9x9";
	}
	System::Void NewGameForm::buttonSize16_Click(System::Object^ sender, System::EventArgs^ e) {
		size = 16;
		boxSize->Text = L"Selected size: 16x16";
	}
	System::Void NewGameForm::buttonDiffEasy_Click(System::Object^ sender, System::EventArgs^ e) {
		diff = Difficulty::Easy;
		boxDifficulty->Text = L"Selected difficulty: Easy";
	}
	System::Void NewGameForm::buttonDiffMedi_Click(System::Object^ sender, System::EventArgs^ e) {
		diff = Difficulty::Medium;
		boxDifficulty->Text = L"Selected difficulty: Medi";
	}
	System::Void NewGameForm::buttonDiffHard_Click(System::Object^ sender, System::EventArgs^ e) {
		diff = Difficulty::Hard;
		boxDifficulty->Text = L"Selected difficulty: Hard";
	}

	System::Void NewGameForm::OnDoWork(System::Object^ sender, DoWorkEventArgs^ e) {
		auto w = safe_cast<BackgroundWorker^>(sender);
		CreateNewGame(size, diff, w, e);
	}

	System::Void NewGameForm::OnWorkerCompleted(System::Object^ sender, RunWorkerCompletedEventArgs^ e) {
		if (e->Error) {
			boxStatus->Text = L"An error occured when generating the level";
		}
		else if (e->Cancelled) {
			boxStatus->Text = L"Cancelled";
		}
		else {
			try {
				game->LoadNewGameToDB();
				boxStatus->Text = L"New level created successfully";
			}
			catch (exep& e) {
				logl(e.msg);
				boxStatus->Text = L"An error occured when generating the level";
			}
		}

		delete game;
		game = nullptr;

		buttonCancel->Enabled = false;
		buttonCancel->Hide();

		stopFromClosing = false;

		buttonBack->Enabled = true;
		buttonBack->Show();
		buttonBack->Focus();

		buttonCreate->Enabled = true;
	}

	System::Void NewGameForm::NewGameForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		if (stopFromClosing) {
			e->Cancel = true;
		}
	}
}
