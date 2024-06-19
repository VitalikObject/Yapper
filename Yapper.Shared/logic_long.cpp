#include "logic_long.h"

using namespace Yapper::Shared::Math;

LogicLong::LogicLong() {
	highInteger = 0;
	lowInteger = 0;
};

LogicLong::LogicLong(int highInteger, int lowInteger) {
	this->highInteger = highInteger;
	this->lowInteger = lowInteger;
}

long long LogicLong::toLong(int highValue, int lowValue) {
	return ((long long)highValue << 32) | (unsigned int)lowValue;
}

int LogicLong::getHigherInt() const {
	return highInteger;
}

int LogicLong::getLowerInt() const {
	return lowInteger;
}

void LogicLong::encode(ByteStream& stream) const {
	stream.writeInt(highInteger);
	stream.writeInt(lowInteger);
}

void LogicLong::decode(ByteStream& stream) {
	highInteger = stream.readInt();
	lowInteger = stream.readInt();
}

std::string LogicLong::toString() const {
	std::ostringstream oss;
	oss << "LogicLong(" << highInteger << "-" << lowInteger << ")";
	return oss.str();
}
