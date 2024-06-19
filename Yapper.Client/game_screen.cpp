#include "game_screen.h"

using namespace Yapper::Client::Screen;

GameScreen::GameScreen(GameMain^ gameMain, Stage^ stage) {
	this->gameMain = gameMain;
	this->stage = stage;
}

GameScreen::~GameScreen() {

}

Void GameScreen::DoWork(Object^ sender, DoWorkEventArgs^ e) {

}

Void GameScreen::ProgressChanged(Object^ sender, ProgressChangedEventArgs^ e) {

}
Void GameScreen::RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {

}

Void GameScreen::RenderOnUiThread() {

}