#pragma once
#include "piranha_message.h"

using namespace Yapper::Shared::Math;

namespace Yapper::Shared::Message::Chat {
	class UpdateChatMessage : public PiranhaMessage {
	private:
		std::string name;
		std::string message;
	public:
		static const int MESSAGE_TYPE = 20201;
		UpdateChatMessage();
		virtual ~UpdateChatMessage();
		virtual void encode();
		virtual void decode();
		virtual int getMessageType() const;
		std::string getName() const;
		void setName(const std::string& name);
		std::string getMessage() const;
		void setMessage(const std::string& message);
	};
}