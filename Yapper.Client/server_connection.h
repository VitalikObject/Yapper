#pragma once
#include "../Yapper.Shared/tcp_connection.h"
#include "../Yapper.Shared/messaging.h"
#include "../Yapper.Shared/piranha_message.h"
#include "../Yapper.Shared/debugger.h"
#include "server_message_handler.h"

using namespace System;
using namespace Yapper::Shared::Debug;
using namespace Yapper::Shared::Network;
using namespace Yapper::Shared::Message;
using namespace Yapper::Client::Handler;

namespace Yapper::Client::Network {
	class ServerConnection {
	private:
		TCPConnection* tcpConnection = nullptr;
		Messaging* messaging = nullptr;
	public:
		static constexpr int PACKET_SIZE = 65535;
		ServerConnection();
		~ServerConnection();
		Void ConnectTo(const char *address = "127.0.0.1", int port = 9339);
		Void StartReceiving();
		Void Send(PiranhaMessage& piranhaMessage);
	};
}