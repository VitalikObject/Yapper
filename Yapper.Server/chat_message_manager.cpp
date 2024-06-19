#include "chat_message_manager.h"

using namespace Yapper::Server::Manager;

list<pair<string, string>> ChatMessageManager::chatLog;

void ChatMessageManager::addMessage(const string& name, const string& message) {
	if (chatLog.size() >= MAX_SIZE) {
		chatLog.pop_front();
	}
	chatLog.emplace_back(name, message);
}

int ChatMessageManager::getSize() {
	return (int)chatLog.size();
}

list<pair<string, string>> ChatMessageManager::getMessages() {
	return chatLog;
}