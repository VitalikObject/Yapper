#pragma once
#include "piranha_message.h"
#include "list"

using std::list;
using std::pair;
using std::string;
using namespace Yapper::Shared::Math;

namespace Yapper::Shared::Message::Chat {
	class FullChatMessage : public PiranhaMessage {
	private:
		list<pair<string, string>> chatLog;
	public:
		static const int MESSAGE_TYPE = 20203;
		FullChatMessage();
		virtual ~FullChatMessage();
		virtual void encode();
		virtual void decode();
		virtual int getMessageType() const;
		list<pair<string, string>> getChatLog() const;
		void setChatLog(list<pair<string, string>> chatLog);
	};
}