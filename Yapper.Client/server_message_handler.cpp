#include "server_message_handler.h"
#include "convert_util.h"
#include "chat_message_manager.h"

using namespace Yapper::Client::Utilities;
using namespace Yapper::Client::Manager;
using namespace Yapper::Client::Handler;

ServerMessageHandler::ServerMessageHandler(Messaging* messaging) : MessageHandlerBase(), messaging(messaging) {
	ServerMessageHandler::registerHandlers();
}

void ServerMessageHandler::registerHandlers() {
	registerHandler(LoginStatusMessage::MESSAGE_TYPE, [this](PiranhaMessage* msg) { this->onLoginStatusMessage(static_cast<LoginStatusMessage*>(msg)); });
	registerHandler(UpdateChatMessage::MESSAGE_TYPE, [this](PiranhaMessage* msg) { this->onUpdateChatMessage(static_cast<UpdateChatMessage*>(msg)); });
	registerHandler(FullChatMessage::MESSAGE_TYPE, [this](PiranhaMessage* msg) { this->onFullChatMessage(static_cast<FullChatMessage*>(msg)); });
}

void ServerMessageHandler::onLoginStatusMessage(LoginStatusMessage* loginStatusMessage) {
	switch (loginStatusMessage->getLoginStatus()) {
		case LoginStatus::Failed:
		{
			GameManager::gameStatus = GameStatus::Logged;
			break;
		}
		case LoginStatus::Logging:
		{
			GameManager::gameStatus = GameStatus::Logging;
			break;
		}
		case LoginStatus::Logged:
		{
			GameManager::gameStatus = GameStatus::Logged;
			break;
		}
		default:
		{
			GameManager::gameStatus = GameStatus::Connecting;
			break;
		}
	}
}

void ServerMessageHandler::onUpdateChatMessage(UpdateChatMessage* updateChatMessage) {
	String^ message = ConvertUtil::ConvertString(updateChatMessage->getName()) + ": " +
						ConvertUtil::ConvertString(updateChatMessage->getMessage());
	ChatMessageManager::Enqueue(message);
}

void ServerMessageHandler::onFullChatMessage(FullChatMessage* fullChatMessage) {
	ChatMessageManager::Clear();

	list<pair<string, string>> chatLog = fullChatMessage->getChatLog();

	for (auto& messagePair : chatLog) {
		String^ message = ConvertUtil::ConvertString(messagePair.first) + ": " +
							ConvertUtil::ConvertString(messagePair.second);
		ChatMessageManager::Enqueue(message);
	}
}