#pragma once
#include <string>
#include <algorithm>

//forward declaration
namespace Yapper::Shared::Math {
	class LogicLong; 
}

using namespace Yapper::Shared::Math;

namespace Yapper::Shared::DataStream {
	class ByteStream {
	private:
		char* buffer;
		int offset = 0;
		int length = 0;
		int bitIdx = 0;
	public:
		ByteStream();
		ByteStream(int capacity);
		ByteStream(char* buffer, int length);
		~ByteStream();
		char* getByteArray() const;
		void setByteArray(char* buffer, int length);
		int getLength() const;
		void writeInt(int value);
		void writeU24(unsigned int value);
		void writeU16(unsigned short value);
		void writeBoolean(bool value);
		void writeByte(int value);
		void writeBytes(char* value, int length);
		void writeBytesWithoutLength(char* value, int length);
		void writeLong(LogicLong& value);
		void writeString(const std::string& value);
		int readInt();
		int readU24();
		unsigned short readU16();
		bool readBoolean();
		char readByte();
		LogicLong readLong();
		std::string readString();
		void ensureCapacity(int capacity);
	};
}