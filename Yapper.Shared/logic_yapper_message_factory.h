#include "logic_message_factory.h"

namespace Yapper::Shared::Message {
	class LogicYapperMessageFactory : public LogicMessageFactory {
	public:
		LogicYapperMessageFactory();
		PiranhaMessage* createMessageByType(int type);
	};
}