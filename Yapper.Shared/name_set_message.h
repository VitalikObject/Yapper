#pragma once
#include "string"
#include "piranha_message.h"

using std::string;
using namespace Yapper::Shared::Math;

namespace Yapper::Shared::Message::Account {
	class NameSetMessage : public PiranhaMessage {
	private:
		bool isNameSet = false;
		string name = "";
	public:
		static const int MESSAGE_TYPE = 10102;
		NameSetMessage();
		virtual ~NameSetMessage();
		virtual void encode();
		virtual void decode();
		virtual int getMessageType() const;
		bool getIsNameSet() const;
		void setIsNameSet(bool isNameSet);
		string getName() const;
		void setName(const string& name);
	};
}