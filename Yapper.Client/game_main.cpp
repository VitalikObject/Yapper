#include "game_main.h"
#include "../Yapper.Shared/login_message.h"

using namespace Yapper::Client::Game;
using namespace Yapper::Shared::Message::Account;

GameMain::GameMain(Stage^ stage) {
	this->stage = stage;
	this->serverConnection = new ServerConnection();
}

GameMain::~GameMain() {
	delete serverConnection;
	if (logoScreen != nullptr) delete logoScreen;
	if (loadingScreen != nullptr) delete loadingScreen;
}

Void GameMain::RenderLogoScreen() {
	logoScreen = gcnew LogoScreen(this, stage);
	GameMain::StartBackgroundWork(logoScreen);
}

Void GameMain::RenderLoadingScreen() {
	if (logoScreen != nullptr) {
		logoScreen->~LogoScreen();
		logoScreen = nullptr;
	}

	loadingScreen = gcnew LoadingScreen(this, stage);
	GameMain::StartBackgroundWork(loadingScreen);

	connectionThread = gcnew Thread(gcnew ThreadStart(this, &GameMain::Connect));
	connectionThread->Start();
}

Void GameMain::RenderNameScreen() {
	if (loadingScreen != nullptr) {
		loadingScreen->~LoadingScreen();
		loadingScreen = nullptr;
	}

	nameScreen = gcnew NameScreen(this, stage);
	GameMain::StartBackgroundWork(nameScreen);
}

Void GameMain::RenderMessageScreen() {
	if (loadingScreen != nullptr) {
		loadingScreen->~LoadingScreen();
		loadingScreen = nullptr;
	}

	if (nameScreen != nullptr) {
		nameScreen->~NameScreen();
		nameScreen = nullptr;
	}

	messageScreen = gcnew MessageScreen(this, stage);
	GameMain::StartBackgroundWork(messageScreen);
}

Void GameMain::StartBackgroundWork(GameScreen^ gameScreen) {
	BackgroundWorker^ worker = gcnew BackgroundWorker();
	worker->WorkerReportsProgress = true;
	worker->DoWork += gcnew DoWorkEventHandler(gameScreen, &GameScreen::DoWork);
	worker->ProgressChanged += gcnew ProgressChangedEventHandler(gameScreen, &GameScreen::ProgressChanged);
	worker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler(gameScreen, &GameScreen::RunWorkerCompleted);
	worker->RunWorkerAsync();
}

Void GameMain::Connect() {
	serverConnection->ConnectTo();

	this->saveUtil = gcnew SaveUtil();
	///this->saveUtil->LoadData();

	GameManager::isNameSet = this->saveUtil->getIsNameSet();
	GameManager::Name = this->saveUtil->getName();

	LoginMessage loginMessage;
	loginMessage.setIsNameSet(saveUtil->getIsNameSet());
	loginMessage.setName(ConvertUtil::ConvertString(saveUtil->getName()));

	serverConnection->Send(loginMessage);

	serverConnection->StartReceiving();
}

Void GameMain::Send(PiranhaMessage& message) {
	serverConnection->Send(message);
}

Void GameMain::Save() {
	saveUtil->setIsNameSet(GameManager::isNameSet);
	saveUtil->setName(GameManager::Name);
	saveUtil->SaveData();
}