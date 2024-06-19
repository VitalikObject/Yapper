#include "logo_screen.h"
#include "loading_screen.h"
#include "game_main.h"

using namespace Yapper::Client::Screen;

LogoScreen::LogoScreen(GameMain^ gameMain, Stage^ stage) : GameScreen(gameMain, stage) {
	label = gcnew Label();
}

LogoScreen::~LogoScreen() {

}

Void LogoScreen::DoWork(Object^ sender, DoWorkEventArgs^ e) {
	stage->Invoke(gcnew MethodInvoker(this, &LogoScreen::RenderOnUiThread));

	for (int i = 0; i < RGB_COLORS; ++i) {
		Thread::Sleep(2);
		(dynamic_cast<BackgroundWorker^>(sender))->ReportProgress(i);
	}

	Thread::Sleep(1000);

	for (int i = RGB_COLORS; i > 0; --i) {
		Thread::Sleep(10);
		(dynamic_cast<BackgroundWorker^>(sender))->ReportProgress(i);
	}
}

Void LogoScreen::ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) {
	label->ForeColor = Color::FromArgb(e->ProgressPercentage, e->ProgressPercentage, e->ProgressPercentage);
}

Void LogoScreen::RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
	stage->Controls->Remove(label);
	gameMain->RenderLoadingScreen();
}

Void LogoScreen::RenderOnUiThread() {
	stage->BackColor = System::Drawing::Color::Black;

	label = gcnew Label();
	label->Text = "A VITALII STRASHNOV PROJECT";
	label->AutoSize = true;
	label->ForeColor = Color::FromArgb(0, 0, 0);
	label->Font = gcnew Font("Arial", 16, System::Drawing::FontStyle::Bold);

	int centerX = (stage->ClientSize.Width - label->Width) / 2;
	centerX += (label->Width - label->PreferredSize.Width) / 2;
	int centerY = (stage->ClientSize.Height - label->Height) / 2;

	label->Location = Point(centerX, centerY);

	stage->Controls->Add(label);
}
