#include "client_message_handler.h"
#include "client_connection.h"
#include "user_manager.h"

using namespace Yapper::Server::Handler;

ClientMessageHandler::ClientMessageHandler(ClientConnection* clientConnection, Messaging messaging) : MessageHandlerBase(), userManager(), messaging(messaging) {
	this->clientConnection = clientConnection;
	ClientMessageHandler::registerHandlers();
}

void ClientMessageHandler::registerHandlers() {
	registerHandler(LoginMessage::MESSAGE_TYPE, [this](PiranhaMessage* msg) { this->onLoginMessage(static_cast<LoginMessage*>(msg)); });
	registerHandler(SendToChatMessage::MESSAGE_TYPE, [this](PiranhaMessage* msg) { this->onSendToChatMessage(static_cast<SendToChatMessage*>(msg)); });
	registerHandler(NameSetMessage::MESSAGE_TYPE, [this](PiranhaMessage* msg) { this->onNameSetMessage(static_cast<NameSetMessage*>(msg)); });
	registerHandler(RequestFullChatMessage::MESSAGE_TYPE, [this](PiranhaMessage* msg) { this->onRequestFullChatMessage(static_cast<RequestFullChatMessage*>(msg)); });
}

void ClientMessageHandler::onLoginMessage(LoginMessage* loginMessage) {
	userManager.setIsNameSet(loginMessage->getIsNameSet());
	
	LoginStatusMessage loginStatusMessage;
	loginStatusMessage.setLoginStatus(LoginStatus::Logging);
	
	FullChatMessage fullChatMessage;
	fullChatMessage.setChatLog(ChatMessageManager::getMessages());

	if (loginMessage->getIsNameSet()) {
		userManager.setName(loginMessage->getName());
		loginStatusMessage.setLoginStatus(LoginStatus::Logged);
	}

	userManager.setLoginStatus(loginStatusMessage.getLoginStatus());
	messaging.send(loginStatusMessage);

	if (loginMessage->getIsNameSet()) messaging.send(fullChatMessage);
}

void ClientMessageHandler::onSendToChatMessage(SendToChatMessage* sendToChatMessage) {
	if (userManager.getIsNameSet()) {
		string name = sendToChatMessage->getName();
		string message = sendToChatMessage->getMessage();

		UpdateChatMessage updateChatMessage;
		updateChatMessage.setName(name);
		updateChatMessage.setMessage(message);

		ChatMessageManager::addMessage(name, message);

		clientConnection->sendMessageToAllClients(updateChatMessage);
	}
}

void ClientMessageHandler::onNameSetMessage(NameSetMessage* nameSetMessage) {
	if (nameSetMessage->getIsNameSet()) {
		userManager.setIsNameSet(nameSetMessage->getIsNameSet());
		userManager.setName(nameSetMessage->getName());

		LoginStatusMessage loginStatusMessage;
		loginStatusMessage.setLoginStatus(LoginStatus::Logged);

		messaging.send(loginStatusMessage);
	}
}

void ClientMessageHandler::onRequestFullChatMessage(RequestFullChatMessage* requestFullChatMessage) {
	if (userManager.getIsNameSet()) {
		FullChatMessage fullchatMessage;
		fullchatMessage.setChatLog(ChatMessageManager::getMessages());

		messaging.send(fullchatMessage);
	}
}