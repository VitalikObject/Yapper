#include "name_screen.h"
#include "game_main.h"

using namespace Yapper::Client::Screen;

NameScreen::NameScreen(GameMain^ gameMain, Stage^ stage) : GameScreen(gameMain, stage) {
	this->label = gcnew Label();
	this->textBox = gcnew TextBox();
	this->okayButton = gcnew Button();
}

NameScreen::~NameScreen() {
}

Void NameScreen::DoWork(Object^ sender, DoWorkEventArgs^ e) {
	stage->Invoke(gcnew MethodInvoker(this, &NameScreen::RenderOnUiThread));
}

Void NameScreen::ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) {

}

Void NameScreen::RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {

}

Void NameScreen::RenderOnUiThread() {
	stage->BackColor = System::Drawing::Color::White;

	label->Text = "Enter your username:";
	label->AutoSize = true;
	label->ForeColor = Color::FromArgb(0, 0, 0);
	label->Font = gcnew Font("Arial", 16, System::Drawing::FontStyle::Bold);

	this->textBox = gcnew TextBox();
	this->textBox->Multiline = false;
	this->textBox->Height = 30;
	this->textBox->Width = 500;
	this->textBox->BackColor = Color::White;
	this->textBox->Font = gcnew System::Drawing::Font(textBox->Font->FontFamily, 16);
	this->textBox->MaxLength = 10;
	this->textBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NameScreen::OnKeyPressed);

	this->okayButton->Text = "Okay";
	this->okayButton->Height = 50;
	this->okayButton->Font = gcnew System::Drawing::Font(okayButton->Font->FontFamily, 16);
	this->okayButton->Click += gcnew EventHandler(this, &NameScreen::OnOkayButtonClick);

	int textBoxCenterX = (stage->ClientSize.Width - textBox->Width) / 2;
	int textBoxCenterY = (stage->ClientSize.Height - textBox->Height) / 2;

	int labelCenterX = (stage->ClientSize.Width - label->Width) / 2;
	labelCenterX += (label->Width - label->PreferredSize.Width) / 2;

	int buttonCenterX = (stage->ClientSize.Width - okayButton->Width) / 2;
	buttonCenterX += (okayButton->Width - okayButton->PreferredSize.Width) / 2;

	textBox->Location = Point(textBoxCenterX, textBoxCenterY);
	label->Location = Point(labelCenterX, textBoxCenterY - 40);
	okayButton->Location = Point(buttonCenterX, textBoxCenterY + 40);

	this->stage->Controls->Add(label);
	this->stage->Controls->Add(textBox);
	this->stage->Controls->Add(okayButton);
}

Void NameScreen::OnOkayButtonClick(Object^ sender, EventArgs^ e) {
	OnNameSet();
}

Void NameScreen::OnKeyPressed(Object^ sender, KeyEventArgs^ e) {
	if (e->KeyCode == Keys::Enter) {
		OnNameSet();
	}
}

Void NameScreen::OnNameSet() {
	String^ name = this->textBox->Text;

	if (name->Length >= 1) {
		GameManager::isNameSet = true;
		GameManager::Name = name;

		this->stage->Controls->Remove(label);
		this->stage->Controls->Remove(textBox);
		this->stage->Controls->Remove(okayButton);

		gameMain->Save();
		gameMain->RenderMessageScreen();

		NameSetMessage nameSetMessage;
		nameSetMessage.setIsNameSet(GameManager::isNameSet);
		nameSetMessage.setName(ConvertUtil::ConvertString(GameManager::Name));
		gameMain->Send(nameSetMessage);

		RequestFullChatMessage requestFullChatMessage;
		gameMain->Send(requestFullChatMessage);
	}
}