#include "login_message.h"
#include "name_set_message.h"
#include "full_chat_message.h"
#include "update_chat_message.h"
#include "login_status_message.h"
#include "send_to_chat_message.h"
#include "request_full_chat_message.h"
#include "logic_yapper_message_factory.h"

using namespace Yapper::Shared::Message;
using namespace Yapper::Shared::Message::Chat;
using namespace Yapper::Shared::Message::Account;

LogicYapperMessageFactory::LogicYapperMessageFactory() : LogicMessageFactory() {}

PiranhaMessage* LogicYapperMessageFactory::createMessageByType(int type) {
	PiranhaMessage* message = nullptr;

	if (type < 20000) {
		switch (type) {
			case LoginMessage::MESSAGE_TYPE:
			{
				message = new LoginMessage();
				break;
			}
			case SendToChatMessage::MESSAGE_TYPE:
			{
				message = new SendToChatMessage();
				break;
			}
			case RequestFullChatMessage::MESSAGE_TYPE:
			{
				message = new RequestFullChatMessage();
				break;
			}
			case NameSetMessage::MESSAGE_TYPE:
			{
				message = new NameSetMessage();
				break;
			}
		}
	}
	else {
		switch (type) {
			case LoginStatusMessage::MESSAGE_TYPE:
			{
				message = new LoginStatusMessage();
				break;
			}
			case UpdateChatMessage::MESSAGE_TYPE:
			{
				message = new UpdateChatMessage();
				break;
			}
			case FullChatMessage::MESSAGE_TYPE:
			{
				message = new FullChatMessage();
				break;
			}
		}
	}

	return message;
}

