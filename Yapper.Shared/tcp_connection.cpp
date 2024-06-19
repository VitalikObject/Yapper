#include "tcp_connection.h"

using namespace Yapper::Shared::Debug;
using namespace Yapper::Shared::Network;

TCPConnection::TCPConnection() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        Debugger::error("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tcpSocket == INVALID_SOCKET) {
        Debugger::error("Could not create socket");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

TCPConnection::TCPConnection(SOCKET tcpSocket) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        Debugger::error("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    this->tcpSocket = tcpSocket;
}

TCPConnection::~TCPConnection() {
    closesocket(tcpSocket);
    WSACleanup();
}

void TCPConnection::bindAndListen(int port) const {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(tcpSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        Debugger::error("Could not bind to port");
        exit(EXIT_FAILURE);
    }

    if (listen(tcpSocket, SOMAXCONN) == SOCKET_ERROR) {
        Debugger::error("Could not listen on socket");
        exit(EXIT_FAILURE);
    }

    Debugger::print("%s %d%s", "Server listening on port", port, "...");
}

SOCKET TCPConnection::acceptConnection() const {
    sockaddr_in clientAddr{};
    int clientAddrLen = sizeof(clientAddr);
    SOCKET clientSocket = accept(tcpSocket, (sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        Debugger::error("Could not accept incoming connection");
        exit(EXIT_FAILURE);
    }

    Debugger::print("Connection accepted");

    return clientSocket;
}

void TCPConnection::connectTo(const char* address, int port) const {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, address, &serverAddr.sin_addr) != 1) {
        Debugger::error("Invalid IP address");
        exit(EXIT_FAILURE);
    }

    if (connect(tcpSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        Debugger::error("Could not connect");
        exit(EXIT_FAILURE);
    }

    Debugger::Debugger::print("Connected successfully");
}

void TCPConnection::sendData(const char* data, int length) const {
    if (send(tcpSocket, data, length, 0) == SOCKET_ERROR) {
        Debugger::error("Could not send data");
        exit(EXIT_FAILURE);
    }

    //Debugger::print("Message sent successfully!");
}

SOCKET TCPConnection::getTCPSocket() {
    return tcpSocket;
}