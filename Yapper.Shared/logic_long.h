#pragma once
#include "byte_stream.h"
#include <sstream>

using namespace Yapper::Shared::DataStream;

namespace Yapper::Shared::Math {
	class LogicLong {
	private:
		int highInteger;
		int lowInteger;
	public:
		LogicLong();
		LogicLong(int highInteger, int lowInteger);
		static long long toLong(int highInteger, int lowInteger);
		int getHigherInt() const;
		int getLowerInt() const;
		void encode(ByteStream& stream) const;
		void decode(ByteStream& stream);
		std::string toString() const;
	};
}