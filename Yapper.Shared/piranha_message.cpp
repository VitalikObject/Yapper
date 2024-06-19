#include "piranha_message.h"

using namespace Yapper::Shared::Message;

PiranhaMessage::PiranhaMessage() : stream() {};

PiranhaMessage::~PiranhaMessage() {

}

void PiranhaMessage::decode() {

}

void PiranhaMessage::encode() {

}

int PiranhaMessage::getMessageType() const {
	return 0;
}

char* PiranhaMessage::getMessageBytes() const {
	return stream.getByteArray();
}

int PiranhaMessage::getEncodingLength() const{
	return stream.getLength();
}

ByteStream& PiranhaMessage::getByteStream() {
	return stream;
}