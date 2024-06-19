#include "login_status_message.h"

using namespace Yapper::Shared::Message::Account;

LoginStatusMessage::LoginStatusMessage() : PiranhaMessage() {}

LoginStatusMessage::~LoginStatusMessage() {
}

void LoginStatusMessage::encode() {
	PiranhaMessage::encode();

	stream.writeInt(loginStatus);
}

void LoginStatusMessage::decode() {
	PiranhaMessage::decode();

	loginStatus = (LoginStatus)stream.readInt();
}

int LoginStatusMessage::getMessageType() const {
	return MESSAGE_TYPE;
}

LoginStatus LoginStatusMessage::getLoginStatus() const {
	return loginStatus;
}

void LoginStatusMessage::setLoginStatus(LoginStatus loginStatus) {
	this->loginStatus = loginStatus;
}