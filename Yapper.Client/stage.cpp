#include "stage.h"
#include "game_main.h"

using namespace Yapper::Client::Game;
using namespace Yapper::Client;

Stage::Stage(void) {
	InitializeComponent();
}

Stage::~Stage() {
	if (components) {
		delete components;
	}
}

void Stage::InitializeComponent(void) {
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Stage::typeid));
	this->SuspendLayout();
	// 
	// GameInterface
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(1262, 673);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->MaximizeBox = false;
	this->Name = L"Stage";
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	this->Text = L"Yapper";
	this->Load += gcnew System::EventHandler(this, &Stage::Stage_Load);
	this->ResumeLayout(false);

}

Void Stage::Stage_Load(Object^ sender, EventArgs^ e) {
	GameMain^ gameMain = gcnew GameMain(this);
	gameMain->RenderLogoScreen();
}
