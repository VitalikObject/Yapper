#include "name_set_message.h"

using namespace Yapper::Shared::Message::Account;

NameSetMessage::NameSetMessage() : PiranhaMessage() {}

NameSetMessage::~NameSetMessage() {}

void NameSetMessage::encode() {
	PiranhaMessage::encode();

	stream.writeBoolean(isNameSet);
	if (isNameSet) stream.writeString(name);
}

void NameSetMessage::decode() {
	PiranhaMessage::decode();

	isNameSet = stream.readBoolean();
	if (isNameSet) name = stream.readString();
}

int NameSetMessage::getMessageType() const {
	return MESSAGE_TYPE;
}

bool NameSetMessage::getIsNameSet() const {
	return isNameSet;
}

void NameSetMessage::setIsNameSet(bool isNameSet) {
	this->isNameSet = isNameSet;
}

string NameSetMessage::getName() const {
	return name;
}

void NameSetMessage::setName(const string& name) {
	this->name = name;
}