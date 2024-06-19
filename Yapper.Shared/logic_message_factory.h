#pragma once
#include "piranha_message.h"

namespace Yapper::Shared::Message {
	class LogicMessageFactory {
	public:
		LogicMessageFactory();
		virtual PiranhaMessage* createMessageByType(int type);
	};
}