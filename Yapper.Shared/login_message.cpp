#include "login_message.h"

using namespace Yapper::Shared::Message::Account;

LoginMessage::LoginMessage() : PiranhaMessage() {}

LoginMessage::~LoginMessage() {
}

void LoginMessage::encode() {
	PiranhaMessage::encode();

	stream.writeBoolean(isNameSet);
	if (isNameSet) stream.writeString(name);
}

void LoginMessage::decode() {
	PiranhaMessage::decode();

	isNameSet = stream.readBoolean();
	if (isNameSet) name = stream.readString();
}

int LoginMessage::getMessageType() const {
	return MESSAGE_TYPE;
}

bool LoginMessage::getIsNameSet() const {
	return isNameSet;
}

void LoginMessage::setIsNameSet(bool isNameSet) {
	this->isNameSet = isNameSet;
}

std::string LoginMessage::getName() const {
	return name;
}

void LoginMessage::setName(const std::string& name) {
	this->name = name;
}