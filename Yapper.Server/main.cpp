#include "../Yapper.Shared/tcp_connection.h"
#include "../Yapper.Shared/help_utill.h"
#include "client_connection.h"

using namespace Yapper::Shared::Network;
using namespace Yapper::Server::Network;
using namespace Yapper::Shared::Utilities;

int main() {
    TCPConnection server;
    server.bindAndListen(9339);

    ClientConnection clientConnection(server);
    clientConnection.start();
    clientConnection.joinAll();

    return 0;
}