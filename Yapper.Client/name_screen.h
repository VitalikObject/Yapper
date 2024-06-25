#pragma once
#include "game_screen.h"
#include "../Yapper.Shared/name_set_message.h"
#include "../Yapper.Shared/request_full_chat_message.h"

using namespace System::Threading;
using namespace Yapper::Shared::Message::Chat;
using namespace Yapper::Shared::Message::Account;

namespace Yapper::Client::Screen {
	ref class NameScreen : public GameScreen {
	private:
		Label^ label = nullptr;
		TextBox^ textBox = nullptr;
		Button^ okayButton = nullptr;
		Void OnOkayButtonClick(Object^ sender, EventArgs^ e);
		Void OnKeyPressed(Object^ sender, KeyEventArgs^ e);
		Void OnNameSet();
	public:
		NameScreen(GameMain^ gameMain, Stage^ stage);
		virtual ~NameScreen();
		virtual Void DoWork(Object^ sender, DoWorkEventArgs^ e) override;
		virtual Void ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) override;
		virtual Void RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) override;
		virtual Void RenderOnUiThread() override;
	};
}