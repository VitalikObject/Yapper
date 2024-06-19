#include "request_full_chat_message.h"

using namespace Yapper::Shared::Message::Chat;

RequestFullChatMessage::RequestFullChatMessage() : PiranhaMessage() {}

RequestFullChatMessage::~RequestFullChatMessage() {}

void RequestFullChatMessage::encode() {
	PiranhaMessage::encode();
}

void RequestFullChatMessage::decode() {
	PiranhaMessage::decode();
}

int RequestFullChatMessage::getMessageType() const {
	return MESSAGE_TYPE;
}