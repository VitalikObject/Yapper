#pragma once
#include "byte_stream.h"
#include "tcp_connection.h"
#include "debugger.h"
#include "rc4_encrypter.h"
#include "piranha_message.h"

using namespace Yapper::Shared::DataStream;
using namespace Yapper::Shared::Debug;
using namespace Yapper::Shared::Cryptography;
using namespace Yapper::Shared::Message;

namespace Yapper::Shared::Network {
	class Messaging {
	private:
		TCPConnection& tcpConnection;
		StreamEncrypter* receiveEncrypter = nullptr;
		StreamEncrypter* sendEncrypter = nullptr;
		const string RC4_KEY = "lkhjzcumefugelxcvxzpzmxdjflnsjukwhexup";
	public:
		static constexpr int PACKET_HEADER_LENGTH = 5;
		Messaging(TCPConnection& tcpConnection);
		void initEncrypters(const string& nonce = "nonce");
		PiranhaMessage* onReceive(char* buffer, int length);
		void send(PiranhaMessage& piranhaMessage);
		void readHeader(ByteStream& byteStream, int& messageType, int& messageLength);
		void writeHeader(ByteStream& byteStream, int messageType, int messageLength);
	};
}