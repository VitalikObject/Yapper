#pragma once
#include "piranha_message.h"

using namespace Yapper::Shared::Math;

namespace Yapper::Shared::Message::Chat {
	class RequestFullChatMessage : public PiranhaMessage {
	public:
		static const int MESSAGE_TYPE = 10203;
		RequestFullChatMessage();
		virtual ~RequestFullChatMessage();
		virtual void encode();
		virtual void decode();
		virtual int getMessageType() const;
	};
}