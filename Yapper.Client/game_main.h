#pragma once
#include "logo_screen.h"
#include "loading_screen.h"
#include "message_screen.h"
#include "name_screen.h"
#include "stage.h"
#include "server_connection.h"
#include "save_util.h"
#include "game_manager.h"

using namespace Yapper::Client::Screen;
using namespace Yapper::Client::Network;
using namespace Yapper::Client::Utilities;


namespace Yapper::Client::Game {
	ref class GameMain {
	private:
		Stage^ stage;
		LogoScreen^ logoScreen = nullptr;
		LoadingScreen^ loadingScreen = nullptr;
		NameScreen^ nameScreen = nullptr;
		MessageScreen^ messageScreen = nullptr;
		ServerConnection* serverConnection = nullptr;
		Messaging* messaging = nullptr;
		Thread^ connectionThread = nullptr;
		SaveUtil^ saveUtil = nullptr;
	public:
		GameMain(Stage^ stage);
		~GameMain();
		Void RenderLogoScreen();
		Void RenderLoadingScreen();
		Void RenderNameScreen();
		Void RenderMessageScreen();
		static Void StartBackgroundWork(GameScreen^ gameScren);
		Void Connect();
		Void Send(PiranhaMessage& message);
		Void Save();
	};
}