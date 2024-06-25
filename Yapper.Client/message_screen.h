#pragma once
#include "game_screen.h"
#include "convert_util.h"
#include "chat_message_manager.h"
#include "../Yapper.Shared/send_to_chat_message.h"

using namespace Yapper::Shared::Message::Chat;
using namespace Yapper::Client::Utilities;
using namespace Yapper::Client::Manager;
using namespace System::Windows::Forms;

namespace Yapper::Client::Screen {
	ref class MessageScreen : public GameScreen {
	private:
		System::Windows::Forms::Timer^ timer;
		FlowLayoutPanel^ panel;
		TextBox^ messageBox;
		TextBox^ inputBox;
		Button^ sendButton;
		Void OnSendButtonClick(Object^ sender, EventArgs^ e);
		Void OnTimerTick(Object^ sender, EventArgs^ e);
		Void OnKeyPressed(Object^ sender, KeyEventArgs^ e);
		Void OnMessageSend();
	public:
		MessageScreen(GameMain^ gameMain, Stage^ stage);
		virtual Void DoWork(Object^ sender, DoWorkEventArgs^ e) override;
		virtual Void ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) override;
		virtual Void RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) override;
		virtual Void RenderOnUiThread() override;
	};
}