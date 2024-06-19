#pragma once
#include "stage.h"
#include "game_screen.h"

using namespace System::Threading;

namespace Yapper::Client::Screen {
	ref class LogoScreen : public GameScreen {
	private:
		Label^ label;
		const int RGB_COLORS = 255;
	public:
		LogoScreen(GameMain^ gameMain, Stage^ stage);
		virtual ~LogoScreen();
		virtual Void DoWork(Object^ sender, DoWorkEventArgs^ e) override;
		virtual Void ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) override;
		virtual Void RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) override;
		virtual Void RenderOnUiThread() override;
	};
}