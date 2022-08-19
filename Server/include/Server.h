/**
 * 服务端
 * 用来处理和客户端之间的通信
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#include <arpa/inet.h>
#include <unordered_set>
#include <sys/epoll.h>

#include "Constants.h"
#include "CmdHandler.h"

class Server
{
public:
    /**
     * 获取Server实例
     * Server &server = Server::singleton();
     */
    static Server &singleton(uint32_t addr, uint32_t port);

    //连接服务端
    void connect();

    void run();

private:
    Server(uint32_t addr, uint32_t port);
    Server(const Server &) = delete;
    Server &operator=(const Server &) = delete;

    uint32_t addr;
    uint32_t port;
    fd_t sock;
    fd_t epoll_fd;
    std::unordered_set<fd_t> client_fds;
    CmdHandler &handler;
};

#endif