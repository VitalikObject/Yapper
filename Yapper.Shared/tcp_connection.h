#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "debugger.h"

#pragma comment(lib, "ws2_32.lib") 

namespace Yapper::Shared::Network {
	class TCPConnection {
	private:
		SOCKET tcpSocket;
	public:
		TCPConnection();
		TCPConnection(SOCKET tcpSocket);
		~TCPConnection();
		void bindAndListen(int port) const;
		SOCKET acceptConnection() const;
		void connectTo(const char* address, int port) const;
		void sendData(const char* data, int length) const;
		SOCKET getTCPSocket();
	};
}