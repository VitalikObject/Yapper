#pragma once
#include "user_manager.h"
#include "chat_message_manager.h"
#include "../Yapper.Shared/debugger.h"
#include "../Yapper.Shared/messaging.h"
#include "../Yapper.Shared/login_message.h"
#include "../Yapper.Shared/name_set_message.h"
#include "../Yapper.Shared/full_chat_message.h"
#include "../Yapper.Shared/update_chat_message.h"
#include "../Yapper.Shared/login_status_message.h"
#include "../Yapper.Shared/send_to_chat_message.h"
#include "../Yapper.Shared/message_handler_base.h"
#include "../Yapper.Shared/request_full_chat_message.h"

namespace Yapper::Server::Network {
	class ClientConnection;
}

using namespace Yapper::Shared::Message::Account;
using namespace Yapper::Shared::Message::Chat;
using namespace Yapper::Shared::Network;
using namespace Yapper::Shared::Handler;
using namespace Yapper::Server::Network;
using namespace Yapper::Server::Manager;
using namespace Yapper::Shared::Debug;

namespace Yapper::Server::Handler {
	class ClientMessageHandler : public MessageHandlerBase {
	private:
		ClientConnection* clientConnection;
		UserManager userManager;
		Messaging messaging;
	public:
		ClientMessageHandler(ClientConnection* clientConnection, Messaging messaging);
		void registerHandlers();
		void onLoginMessage(LoginMessage* loginMessage);
		void onSendToChatMessage(SendToChatMessage* sendToChatMessage);
		void onNameSetMessage(NameSetMessage* nameSetMessage);
		void onRequestFullChatMessage(RequestFullChatMessage* requestFullChatMessage);
	};
}