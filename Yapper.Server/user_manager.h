#pragma once
#include "string"
#include "../Yapper.Shared/login_status_message.h"

using std::string;
using namespace Yapper::Shared::Message::Account;

namespace Yapper::Server::Manager {
	class UserManager {
	private:
		bool isNameSet = false;
		string name = "Bulya";
		LoginStatus loginStatus = Failed;
	public:
		UserManager();
		bool getIsNameSet() const;
		void setIsNameSet(bool isNameSet);
		string getName() const;
		void setName(const string& name);
		LoginStatus getLoginStatus() const;
		void setLoginStatus(LoginStatus loginStatus);
	};
}