#include "messaging.h"
#include "logic_yapper_message_factory.h"

using namespace Yapper::Shared::Network;
using namespace Yapper::Shared::Message;

Messaging::Messaging(TCPConnection& tcpConnection) : tcpConnection(tcpConnection) {
	initEncrypters();
}
void Messaging::initEncrypters(const string& nonce) {
	receiveEncrypter = new RC4Encrypter(RC4_KEY, nonce);
	sendEncrypter = new RC4Encrypter(RC4_KEY, nonce);
}

PiranhaMessage* Messaging::onReceive(char* buffer, int length) {
	if (length >= PACKET_HEADER_LENGTH) {
		ByteStream byteStream(buffer, length);

		int messageType, messageLength;
		readHeader(byteStream, messageType, messageLength);

		if (length >= PACKET_HEADER_LENGTH + messageLength && (messageType > 10000 && messageType < 30000)) {
			Debugger::print("Message with type: %d, length: %d received!", messageType, messageLength);

			char* encryptedBytes = new char[messageLength];
			char* encodingBytes = nullptr;

			std::memcpy(encryptedBytes, buffer + PACKET_HEADER_LENGTH, messageLength);

			int encodingLength;

			if (receiveEncrypter != nullptr) {
				encodingLength = messageLength - receiveEncrypter->getOverheadEncryption();
				encodingBytes = new char[encodingLength];

				receiveEncrypter->decrypt(encryptedBytes, encodingBytes, encodingLength);
			}
			else {
				encodingLength = messageLength;
				encodingBytes = encryptedBytes;
			}

			LogicYapperMessageFactory logicYapperMessageFactory;

			PiranhaMessage* piranhaMessage = logicYapperMessageFactory.createMessageByType(messageType);

			if (piranhaMessage != nullptr) {
				piranhaMessage->getByteStream().setByteArray(encodingBytes, encodingLength);
				piranhaMessage->decode();
			}

			if (encodingBytes != nullptr && encodingBytes != encryptedBytes) {
				delete[] encodingBytes;
			}
			if (encryptedBytes != nullptr) {
				delete[] encryptedBytes;
			}

			return piranhaMessage;
		}
	}

	return nullptr;
}

void Messaging::send(PiranhaMessage& piranhaMessage) {
	if (piranhaMessage.getEncodingLength() == 0) {
		piranhaMessage.encode();
	}

	int encodingLength = piranhaMessage.getEncodingLength();
	int encryptedLength;

	char* encodingBytes = piranhaMessage.getMessageBytes();
	char* encryptedBytes;

	if (sendEncrypter != nullptr) {
		encryptedLength = encodingLength + sendEncrypter->getOverheadEncryption();
		encryptedBytes = new char[encryptedLength];

		sendEncrypter->encrypt(encodingBytes, encryptedBytes, encodingLength);
	}
	else {
		encryptedBytes = encodingBytes;
		encryptedLength = encodingLength;
	}

	ByteStream byteStream;
	writeHeader(byteStream, piranhaMessage.getMessageType(), encryptedLength);
	byteStream.writeBytesWithoutLength(encryptedBytes, encryptedLength);

	tcpConnection.sendData(byteStream.getByteArray(), byteStream.getLength());

	Debugger::print("Message with type: %d, length: %d sent successfully!", piranhaMessage.getMessageType(), piranhaMessage.getEncodingLength());

	//delete[] encodingBytes;
	delete[] encryptedBytes;
}

void Messaging::readHeader(ByteStream& byteStream, int& messageType, int& messageLength) {
	messageType = byteStream.readU16();
	messageLength = byteStream.readU24();
}

void Messaging::writeHeader(ByteStream& byteStream, int messageType, int messageLength) {
	byteStream.writeU16(messageType);
	byteStream.writeU24(messageLength);
}

