#pragma once
#include "game_screen.h"
#include "convert_util.h"
#include "game_manager.h"
#include "../Yapper.Shared/help_utill.h"

using namespace System::Threading;
using namespace Yapper::Client::Game;
using namespace Yapper::Client::Utilities;
using namespace Yapper::Shared::Utilities;

namespace Yapper::Client::Screen {
	ref class LoadingScreen : public GameScreen {
	private:
		Image^ backgroundImage;
		ProgressBar^ loadingBar;
		String^ backgroundPath = "\\resources\\loading_screen.jpg";
		Void DrawLoadingBar();
	public:
		LoadingScreen(GameMain^ gameMain, Stage^ stage);
		~LoadingScreen();
		virtual Void DoWork(Object^ sender, DoWorkEventArgs^ e) override;
		virtual Void ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) override;
		virtual Void RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) override;
		virtual Void RenderOnUiThread() override;
	};
}