#include "Server.h"
#include "Json.h"

#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;

Server &Server::singleton(uint32_t addr, uint16_t port)
{
    static bool inited = false;
    if (addr == 0 && port == 0)
    {
        if (!inited)
        {
            cout << "error: please provide the address and port when first get this singleton!" << endl;
            exit(-1);
        }
    }
    static Server singleton(inited, addr, port);
    inited = true;
    return singleton;
}

Server::Server(bool inited, uint32_t addr, uint16_t port) : handler(CmdHandler::singleton())
{
    if (!inited)
        this->addr = addr, this->port = htons(port);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        cout << "socket error" << endl;
        exit(-1);
    }
}

void Server::connect()
{
    sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = port;
    myaddr.sin_addr.s_addr = addr;
    if (bind(sock, (sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
        cout << "bind error" << endl;
        exit(-1);
    }

    listen(sock, 10);

    epoll_fd = epoll_create(256);
    if (epoll_fd == -1)
    {
        cout << "epoll create error" << endl;
        exit(-1);
    }

    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sock;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock, &ev) == -1)
    {
        cout << "add epoll_fd error" << endl;
        exit(-1);
    }
}
char buf[6291456] = {0};
void Server::run()
{
    epoll_event ev;
    epoll_event ret_ev[64];
    int ret_num = 64;
    while (true)
    {
        int nready = epoll_wait(epoll_fd, ret_ev, ret_num, -1);
        if (nready == -1)
        {
            cout << "epoll wait error" << endl;
            continue;
        }
        for (int i = 0; i < nready; i++)
        {

            //有新的客户端接入
            if (ret_ev[i].data.fd == sock && (ret_ev[i].events & EPOLLIN))
            {
                int client = accept(sock, NULL, NULL);
                if (client == -1)
                {
                    cout << "accept error" << endl;
                    continue;
                }

                ev.events = EPOLLIN;
                ev.data.fd = client;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client, &ev);
                client_fds.insert(client);
                cout << "get a new client" << endl;
            }
            else
            {
                //有客户端发送消息
                if (ret_ev[i].events & EPOLLIN)
                {
                    int client = ret_ev[i].data.fd;
                    if (client_fds.find(client) != client_fds.end())
                    {

                        int bytes = recv(client, buf, sizeof(buf), 0);
                        if (bytes == 0 || bytes == -1)
                        {
                            cout << "one client disconnected" << endl;
                            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client, NULL);
                            client_fds.erase(client);
                            auto info = __clients.find(client);
                            if (info != __clients.end())
                            {
                                string username = info->second;
                                clients.erase(username);
                                __clients.erase(info);
                            }
                            continue;
                        }
                        cout << "recv = " << buf << endl;
                        handler.handle(client, buf);
                    }
                }
            }
        }
    }
}

fd_t Server::getFdByName(std::string username)
{
    auto user_fd = clients.find(username);
    if (user_fd != clients.end())
    {
        return user_fd->second;
    }
    return -1;
}

void Server::addClient(std::string username, fd_t __fd)
{
    clients[username] = __fd;
    __clients[__fd] = username;
}
