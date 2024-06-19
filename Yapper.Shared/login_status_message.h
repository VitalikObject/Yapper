#pragma once
#include "logic_long.h"
#include "piranha_message.h"

using namespace Yapper::Shared::Math;

namespace Yapper::Shared::Message::Account {
	enum LoginStatus {
		Logging,
		Logged,
		Failed
	};
	class LoginStatusMessage : public PiranhaMessage {
	private:
		LoginStatus loginStatus = Logged;
	public:
		static const int MESSAGE_TYPE = 20101;
		LoginStatusMessage();
		virtual ~LoginStatusMessage();
		virtual void encode();
		virtual void decode();
		virtual int getMessageType() const;
		LoginStatus getLoginStatus() const;
		void setLoginStatus(LoginStatus loginStatus);
	};
}