#pragma once
#include "byte_stream.h"

using namespace Yapper::Shared::DataStream;

namespace Yapper::Shared::Message {
	class PiranhaMessage {
	protected:
		ByteStream stream;
	public:
		PiranhaMessage();
		virtual ~PiranhaMessage();
		virtual void decode();
		virtual void encode();
		virtual int getMessageType() const;
		char* getMessageBytes() const;
		int getEncodingLength() const;
		ByteStream& getByteStream();
	};
}