#pragma once
#include "stage.h"

// forward declaration
namespace Yapper::Client::Game {
	ref class GameMain;
}

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Yapper::Client::Game;

namespace Yapper::Client::Screen {
	ref class GameScreen abstract {
	protected:
		GameMain^ gameMain;
		Stage^ stage;
	public:
		GameScreen(GameMain^ gameMain, Stage^ stage);
		virtual ~GameScreen();
		virtual Void DoWork(Object^ sender, DoWorkEventArgs^ e);
		virtual Void ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e);
		virtual Void RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e);
		virtual Void RenderOnUiThread();
	};
}