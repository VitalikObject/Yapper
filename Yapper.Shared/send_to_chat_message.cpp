#include "send_to_chat_message.h"

using namespace Yapper::Shared::Message::Chat;

SendToChatMessage::SendToChatMessage() : PiranhaMessage() {}

SendToChatMessage::~SendToChatMessage() {
}

void SendToChatMessage::encode() {
	PiranhaMessage::encode();

	stream.writeString(name);
	stream.writeString(message);
}

void SendToChatMessage::decode() {
	PiranhaMessage::decode();

	name = stream.readString();
	message = stream.readString();
}

int SendToChatMessage::getMessageType() const {
	return MESSAGE_TYPE;
}

std::string SendToChatMessage::getName() const {
	return name;
}

void SendToChatMessage::setName(const std::string& name) {
	this->name = name;
}

std::string SendToChatMessage::getMessage() const {
	return message;
}

void SendToChatMessage::setMessage(const std::string& message) {
	this->message = message;
}
