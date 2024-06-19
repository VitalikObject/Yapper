#pragma once
#include <vcclr.h>
#include "game_manager.h"
#include "../Yapper.Shared/messaging.h"
#include "../Yapper.Shared/full_chat_message.h"
#include "../Yapper.Shared/update_chat_message.h"
#include "../Yapper.Shared/login_status_message.h"
#include "../Yapper.Shared/message_handler_base.h"

using namespace Yapper::Shared::Message::Account;
using namespace Yapper::Shared::Message::Chat;
using namespace Yapper::Shared::Handler;
using namespace Yapper::Shared::Network;
using namespace Yapper::Client::Game;

namespace Yapper::Client::Handler {
	class ServerMessageHandler : public MessageHandlerBase {
	private:
		Messaging* messaging;
	public:
		ServerMessageHandler(Messaging* messaging);
		void registerHandlers();
		void onLoginStatusMessage(LoginStatusMessage* loginMessage);
		void onUpdateChatMessage(UpdateChatMessage* updateChatMessage);
		void onFullChatMessage(FullChatMessage* fullChatMessage);
	};
}