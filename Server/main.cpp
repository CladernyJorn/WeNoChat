#include "Server.h"

int main()
{
    Server &server = Server::singleton(INADDR_ANY, 8888);
    server.connect();
    server.run();
    return 0;
}