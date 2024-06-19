#include "full_chat_message.h"

using namespace Yapper::Shared::Message::Chat;

FullChatMessage::FullChatMessage() : PiranhaMessage() {}

FullChatMessage::~FullChatMessage() {}

void FullChatMessage::encode() {
	PiranhaMessage::encode();

	stream.writeInt((int)chatLog.size());
	for (auto& message : chatLog) {
		stream.writeString(message.first);
		stream.writeString(message.second);
	}
}

void FullChatMessage::decode() {
	PiranhaMessage::decode();

	int size = stream.readInt();
	for (int i = 0; i < size; ++i) {
		string name = stream.readString();
		string message = stream.readString();

		chatLog.emplace_back(name, message);
	}
}

int FullChatMessage::getMessageType() const {
	return MESSAGE_TYPE;
}

list<pair<string, string>> FullChatMessage::getChatLog() const {
	return chatLog;
}

void FullChatMessage::setChatLog(list<pair<string, string>> chatLog) {
	this->chatLog = chatLog;
}