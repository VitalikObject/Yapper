#include "byte_stream.h"
#include "logic_long.h"

using namespace Yapper::Shared::DataStream;

ByteStream::ByteStream() {
	buffer = new char[10];
	std::fill(buffer, buffer + 10, '\0');
	length = 10;
}

ByteStream::ByteStream(int capacity) {
	buffer = new char[capacity];
	std::fill(buffer, buffer + capacity, '\0');
	length = capacity;
}

ByteStream::ByteStream(char* buffer, int length) {
	this->buffer = buffer;
	this->length = length;
}

ByteStream::~ByteStream() {
}

char* ByteStream::getByteArray() const {
	return buffer;
}

void ByteStream::setByteArray(char* buffer, int length) {
	deleteByteArray();

	this->buffer = buffer;
	this->length = length;
}

void ByteStream::deleteByteArray() {
	if (buffer != nullptr) {
		delete[] buffer;
		buffer = nullptr;
	}
}

int ByteStream::getLength() const {
	return offset;
}

void ByteStream::writeInt(int value) {
	ensureCapacity(4);
	bitIdx = 0;

	buffer[offset++] = (char)((value >> 24) & 0xFF);
	buffer[offset++] = (char)((value >> 16) & 0xFF);
	buffer[offset++] = (char)((value >> 8) & 0xFF);
	buffer[offset++] = (char)(value & 0xFF);
}

void ByteStream::writeU24(unsigned int value) {
	ensureCapacity(3);
	bitIdx = 0;

	buffer[offset++] = (char)((value >> 16) & 0xFF);
	buffer[offset++] = (char)((value >> 8) & 0xFF);
	buffer[offset++] = (char)(value & 0xFF);
}

void ByteStream::writeU16(unsigned short value) {
	ensureCapacity(2);
	bitIdx = 0;

	buffer[offset++] = (char)((value >> 8) & 0xFF);
	buffer[offset++] = (char)(value & 0xFF);
}

void ByteStream::writeBoolean(bool value) {
	if (bitIdx == 0) {
		ensureCapacity(1);
		buffer[offset++] = 0;
	}

	if (value) {
		buffer[offset - 1] |= (char)(1 << bitIdx);
	}

	bitIdx = (bitIdx + 1) & 7;
}

void ByteStream::writeByte(int value) {
	ensureCapacity(1);
	bitIdx = 0;

	buffer[offset++] = (char)(value);
}

void ByteStream::writeBytes(char* value, int length) {
	bitIdx = 0;

	ByteStream::writeInt(length);
	ByteStream::writeBytesWithoutLength(value, length);
}

void ByteStream::writeBytesWithoutLength(char* value, int length) {
	ensureCapacity(length);
	bitIdx = 0;

	for (int i = 0; i < length; ++i) {
		writeByte(value[i]);
	}
}

void ByteStream::writeLong(LogicLong& value) {
	ensureCapacity(8);
	bitIdx = 0;

	value.encode(*this);
}

void ByteStream::writeString(const std::string& value) {
	writeInt((int)value.length());

	ensureCapacity((int)value.length());

	for (char val : value) {
		buffer[offset++] = val;
	}
}

int ByteStream::readInt() {
	bitIdx = 0;

	return ((buffer[offset++] & 0xFF) << 24) |
			((buffer[offset++] & 0xFF) << 16) |
			((buffer[offset++] & 0xFF) << 8) |
			(buffer[offset++] & 0xFF);
}

int ByteStream::readU24() {
	bitIdx = 0;

	return ((buffer[offset++] & 0xFF) << 16) |
			((buffer[offset++] & 0xFF) << 8) |
			(buffer[offset++] & 0xFF);
}

unsigned short ByteStream::readU16() {
	bitIdx = 0;

	return ((buffer[offset++] & 0xFF) << 8) |
			(buffer[offset++] & 0xFF);
}

bool ByteStream::readBoolean() {
	if (bitIdx == 0) {
		++offset;
	}

	bool value = (buffer[offset - 1] & (1 << bitIdx)) != 0;
	bitIdx = (bitIdx + 1) & 7;
	return value;
}

char ByteStream::readByte() {
	bitIdx = 0;

	return buffer[offset++];
}

LogicLong ByteStream::readLong() {
	bitIdx = 0;

	LogicLong logicLong;
	logicLong.decode(*this);
	return logicLong;
}

std::string ByteStream::readString() {
	int length = readInt();
	std::string value;

	for (int i = 0; i < length; ++i) {
		value += buffer[offset++];
	}

	return value;
}

void ByteStream::ensureCapacity(int capacity) {
	int bufferLength = length;

	if (offset + capacity > bufferLength) {
		int newCapacity = bufferLength + capacity + 100;
		char* tempBuffer = new char[newCapacity];
		std::copy(buffer, buffer + bufferLength, tempBuffer);
		delete[] buffer;
		buffer = tempBuffer;
		length = newCapacity;
	}
}