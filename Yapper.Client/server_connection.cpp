#include "server_connection.h"

using namespace Yapper::Client::Network;

ServerConnection::ServerConnection() {
    tcpConnection = new TCPConnection();
    messaging = new Messaging(*tcpConnection);
}

ServerConnection::~ServerConnection() {
    delete messaging;
    delete tcpConnection;
}

Void ServerConnection::ConnectTo(const char *address, int port) {
	tcpConnection->connectTo(address, port);
}

Void ServerConnection::StartReceiving() {
    char buffer[PACKET_SIZE] = { 0 };
    SOCKET serverSocket = tcpConnection->getTCPSocket();
    ServerMessageHandler serverMessageHandler(messaging);

    while (true) {
        int totalBytesReceived = 0;
        int bytesReceived = recv(serverSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            closesocket(serverSocket);
            Debugger::print("Server closed the connection");
            return;
        }

        totalBytesReceived += bytesReceived;

        while (totalBytesReceived > 0) {
            PiranhaMessage* message = messaging->onReceive(buffer, totalBytesReceived);
            if (!message)
                break; 

            serverMessageHandler.handleMessage(message);

            int remainingBytes = totalBytesReceived - message->getEncodingLength() + Messaging::PACKET_HEADER_LENGTH;
            memmove(buffer, buffer + message->getEncodingLength() + Messaging::PACKET_HEADER_LENGTH, remainingBytes);
            totalBytesReceived = remainingBytes;

            delete message;
        }

        memset(buffer, 0, sizeof(buffer));
    }
}

Void ServerConnection::Send(PiranhaMessage& piranhaMessage) {
    messaging->send(piranhaMessage);
}
