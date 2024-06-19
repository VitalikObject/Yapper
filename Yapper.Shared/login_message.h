#pragma once
#include "piranha_message.h"

using namespace Yapper::Shared::Math;

namespace Yapper::Shared::Message::Account {
	class LoginMessage : public PiranhaMessage {
	private:
		bool isNameSet = false;
		std::string name = "";
	public:
		static const int MESSAGE_TYPE = 10101;
		LoginMessage();
		virtual ~LoginMessage();
		virtual void encode();
		virtual void decode();
		virtual int getMessageType() const;
		bool getIsNameSet() const;
		void setIsNameSet(bool isNameSet);
		std::string getName() const;
		void setName(const std::string& name);
	};
}