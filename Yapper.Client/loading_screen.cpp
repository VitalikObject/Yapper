#include "loading_screen.h"
#include "game_main.h"

using namespace Yapper::Client::Screen;

LoadingScreen::LoadingScreen(GameMain^ gameMain, Stage^ stage) : GameScreen(gameMain, stage) {
	loadingBar = gcnew ProgressBar();
	DrawLoadingBar();
}

LoadingScreen::~LoadingScreen() {

}

Void LoadingScreen::DrawLoadingBar() {
	loadingBar->Location = System::Drawing::Point(0, stage->ClientSize.Height - 30);
	loadingBar->Size = System::Drawing::Size(stage->ClientSize.Width, 30);
	loadingBar->Style = ProgressBarStyle::Continuous;
	stage->Controls->Add(loadingBar);
}

Void LoadingScreen::DoWork(Object^ sender, DoWorkEventArgs^ e) {
	stage->Invoke(gcnew MethodInvoker(this, &LoadingScreen::RenderOnUiThread));

	for (int i = 0; i <= 80; ++i) {
		System::Threading::Thread::Sleep(50);
		(dynamic_cast<BackgroundWorker^>(sender))->ReportProgress(i);
	}

	while (GameManager::gameStatus == GameStatus::Connecting) {};

	for (int i = 81; i <= 100; ++i) {
		System::Threading::Thread::Sleep(50);
		(dynamic_cast<BackgroundWorker^>(sender))->ReportProgress(i);
	}
}

Void LoadingScreen::ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) {
	loadingBar->Value = e->ProgressPercentage;
}

Void LoadingScreen::RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
	stage->BackgroundImage = nullptr;
	stage->Controls->Remove(loadingBar);

	if (GameManager::isNameSet)	gameMain->RenderMessageScreen();
	else gameMain->RenderNameScreen();
}

Void LoadingScreen::RenderOnUiThread() {
	std::string currentDirectory = HelpUtil::getCurrentDirectory();
	String^ imagePath = ConvertUtil::ConvertString(currentDirectory) + backgroundPath;

	backgroundImage = Image::FromFile(imagePath);
	stage->BackgroundImage = backgroundImage;
	stage->BackgroundImageLayout = ImageLayout::Stretch;
}