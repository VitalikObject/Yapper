#include "user_manager.h"

using namespace Yapper::Server::Manager;

UserManager::UserManager() {

}

bool UserManager::getIsNameSet() const {
	return isNameSet;
}

void UserManager::setIsNameSet(bool isNameSet) {
	this->isNameSet = isNameSet;
}

string UserManager::getName() const {
	return name;
}

void UserManager::setName(const string& name) {
	this->name = name;
}

LoginStatus UserManager::getLoginStatus() const {
	return loginStatus;
}

void UserManager::setLoginStatus(LoginStatus loginStatus) {
	this->loginStatus = loginStatus;
}
