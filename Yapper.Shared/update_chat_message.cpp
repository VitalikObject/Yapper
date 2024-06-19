#include "update_chat_message.h"

using namespace Yapper::Shared::Message::Chat;

UpdateChatMessage::UpdateChatMessage() : PiranhaMessage() {}

UpdateChatMessage::~UpdateChatMessage() {
}

void UpdateChatMessage::encode() {
	PiranhaMessage::encode();

	stream.writeString(name);
	stream.writeString(message);
}

void UpdateChatMessage::decode() {
	PiranhaMessage::decode();

	name = stream.readString();
	message = stream.readString();
}

int UpdateChatMessage::getMessageType() const {
	return MESSAGE_TYPE;
}

std::string UpdateChatMessage::getName() const {
	return name;
}

void UpdateChatMessage::setName(const std::string& name) {
	this->name = name;
}

std::string UpdateChatMessage::getMessage() const {
	return message;
}

void UpdateChatMessage::setMessage(const std::string& message) {
	this->message = message;
}
