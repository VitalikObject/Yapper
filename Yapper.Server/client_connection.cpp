#include "client_connection.h"

using namespace Yapper::Server::Network;

ClientConnection::ClientConnection(TCPConnection& server) : server(server) {

}

ClientConnection::~ClientConnection() {

}

void ClientConnection::handleClient(SOCKET clientSocket) {
    std::unique_ptr<char[]> buffer(new char[PACKET_SIZE]());
    TCPConnection clientConnection(clientSocket);
    Messaging messaging(clientConnection);
    ClientMessageHandler clientMessageHandler(this, messaging);

    {
        std::lock_guard<std::mutex> lock(clientConnectionsMutex);
        clientConnections.push_back(&messaging);
    }

    while (true) {
        int totalBytesReceived = 0;
        int bytesReceived = recv(clientSocket, buffer.get(), PACKET_SIZE, 0);
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            closesocket(clientSocket);
            Debugger::print("Client closed the connection");

            std::lock_guard<std::mutex> lock(clientConnectionsMutex);
            clientConnections.erase(std::remove(clientConnections.begin(), clientConnections.end(), &messaging), clientConnections.end());
            return;
        }
        
        totalBytesReceived += bytesReceived;

        while (totalBytesReceived > 0) {
            PiranhaMessage* message = messaging.onReceive(buffer.get(), totalBytesReceived);
            if (!message)
                break;

            clientMessageHandler.handleMessage(message);

            int remainingBytes = totalBytesReceived - message->getEncodingLength() + 5;
            memmove(buffer.get(), buffer.get() + message->getEncodingLength() + 5, remainingBytes);
            totalBytesReceived = remainingBytes;

            delete message;
        }

        memset(buffer.get(), 0, sizeof(buffer));
    }
}

void ClientConnection::start() {
    while (true) {
        SOCKET clientSocket = server.acceptConnection();
        if (clientSocket != INVALID_SOCKET) {
            threads.emplace_back(&ClientConnection::handleClient, this, clientSocket);
        }
    }
}

void ClientConnection::joinAll() {
    for (auto& thread : threads) {
        thread.join();
    }
}

void ClientConnection::sendMessageToAllClients(PiranhaMessage& message) {
    std::lock_guard<std::mutex> lock(clientConnectionsMutex);
    for (auto& client : clientConnections) {
        client->send(message);
    }

    message.getByteStream().deleteByteArray();
}