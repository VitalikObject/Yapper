#include "message_screen.h"
#include "game_main.h"

using namespace Yapper::Client::Screen;

MessageScreen::MessageScreen(GameMain^ gameMain, Stage^ stage) : GameScreen(gameMain, stage) {
	this->timer = gcnew System::Windows::Forms::Timer();
	this->timer->Interval = 100;
	this->timer->Tick += gcnew EventHandler(this, &MessageScreen::OnTimerTick);
}

Void MessageScreen::DoWork(Object^ sender, DoWorkEventArgs^ e) {
	stage->Invoke(gcnew MethodInvoker(this, &MessageScreen::RenderOnUiThread));
}

Void MessageScreen::ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) {

}

Void MessageScreen::RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {

}

Void MessageScreen::RenderOnUiThread() {
	this->panel = gcnew FlowLayoutPanel();
	this->panel->Height = 50;
	this->panel->Dock = DockStyle::Bottom;  
	this->panel->WrapContents = false;  

	stage->BackColor = Color::White;

	this->messageBox = gcnew TextBox();
	this->messageBox->Multiline = true;
	this->messageBox->ScrollBars = ScrollBars::Vertical;
	this->messageBox->ReadOnly = true;
	this->messageBox->Height = 480;
	this->messageBox->Dock = DockStyle::Top;
	this->messageBox->BackColor = Color::White;
	this->messageBox->Font = gcnew System::Drawing::Font(messageBox->Font->FontFamily, 16);

	this->inputBox = gcnew TextBox();
	this->inputBox->Multiline = false;
	this->inputBox->Height = 50;
	this->inputBox->Width = 860;
	this->inputBox->Dock = DockStyle::Bottom;
	this->inputBox->Font = gcnew System::Drawing::Font(inputBox->Font->FontFamily, 16);
	this->inputBox->MaxLength = 500;
	this->inputBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MessageScreen::OnKeyPressed);

	this->sendButton = gcnew Button();
	this->sendButton->Text = "Send";
	this->sendButton->Height = 50;
	this->sendButton->Dock = DockStyle::Right;
	this->sendButton->Click += gcnew EventHandler(this, &MessageScreen::OnSendButtonClick);
	this->sendButton->Font = gcnew System::Drawing::Font(sendButton->Font->FontFamily, 16);

	this->panel->Controls->Add(this->inputBox);
	this->panel->Controls->Add(this->sendButton);

	this->stage->Controls->Add(this->messageBox);
	this->stage->Controls->Add(panel);

	this->timer->Start();
}

Void MessageScreen::OnSendButtonClick(Object^ sender, EventArgs^ e) {
	OnMessageSend();
}

Void MessageScreen::OnTimerTick(Object^ sender, EventArgs^ e) {
	int queueLength = ChatMessageManager::GetLength();
	if (queueLength > 0) {
		for (int i = 0; i < queueLength; ++i) {
			this->messageBox->AppendText(ChatMessageManager::Dequeue() + "\r\n");
			this->messageBox->ScrollToCaret();
		}
	}
}

Void MessageScreen::OnKeyPressed(Object^ sender, KeyEventArgs^ e) {
	if (e->KeyCode == Keys::Enter) {
		OnMessageSend();
	}
}

Void MessageScreen::OnMessageSend() {
	String^ message = this->inputBox->Text;

	if (message->Length >= 1) {
		this->inputBox->Text = String::Empty;

		SendToChatMessage sendToChatMessage;
		sendToChatMessage.setName(ConvertUtil::ConvertString(GameManager::Name));
		sendToChatMessage.setMessage(ConvertUtil::ConvertString(message));

		gameMain->Send(sendToChatMessage);
	}
}