#pragma once
#include "string"
#include <list>

using std::string;
using std::list;
using std::pair;

namespace Yapper::Server::Manager {
	class ChatMessageManager {
	private:
		static list<pair<string, string>> chatLog;
		static const int MAX_SIZE = 200;
	public:
		static void addMessage(const string& name, const string& message);
		static int getSize();
		static list<pair<string, string>> getMessages();
	};
}