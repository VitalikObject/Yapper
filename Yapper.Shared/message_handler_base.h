#pragma once 
#include <functional>
#include "piranha_message.h"

using namespace Yapper::Shared::Message;

namespace Yapper::Shared::Handler {
	class MessageHandlerBase {
	public:
		using HandlerFunc = std::function<void(PiranhaMessage*)>;
		MessageHandlerBase();
		virtual ~MessageHandlerBase() = default;
		void registerHandler(int messageType, HandlerFunc handler);
		bool handleMessage(PiranhaMessage* message);
	private:
		std::unordered_map<int, HandlerFunc> handlers;
	};
}