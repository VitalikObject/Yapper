#include <vector>
#include <thread>
#include <mutex>
#include "client_message_handler.h"
#include "../Yapper.Shared/debugger.h"
#include "../Yapper.Shared/messaging.h"
#include "../Yapper.Shared/byte_stream.h"
#include "../Yapper.Shared/tcp_connection.h"
#include "../Yapper.Shared/message_handler_base.h"

using namespace Yapper::Shared::DataStream;
using namespace Yapper::Server::Handler;
using namespace Yapper::Shared::Handler;
using namespace Yapper::Shared::Network;
using namespace Yapper::Shared::Debug;

namespace Yapper::Server::Network {
    class ClientConnection {
    private:
        TCPConnection& server;
        std::vector<std::thread> threads;
        std::vector<Messaging*> clientConnections;
        std::mutex clientConnectionsMutex;
        void handleClient(SOCKET clientSocket);
    public:
        static constexpr int PACKET_SIZE = 65535;
        ClientConnection(TCPConnection& server);
        ~ClientConnection();
        void start();
        void joinAll();
        void sendMessageToAllClients(PiranhaMessage& piranhaMessage);
    };
}