#include "Server.h"
#include "Json.h"
#include "Tools.h"

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
using namespace std;

Server &Server::singleton(uint32_t addr, uint16_t port, uint16_t filePort)
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
    static Server singleton(inited, addr, port, filePort);
    inited = true;
    return singleton;
}

Server::Server(bool inited, uint32_t addr, uint16_t port, uint16_t filePort) : handler(CmdHandler::singleton())
{
    if (!inited)
        this->addr = addr, this->port = htons(port), this->filePort = htons(filePort);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        cout << "socket error" << endl;
        exit(-1);
    }
    fileSock = socket(AF_INET, SOCK_STREAM, 0);
    if (fileSock == -1)
    {
        cout << "file socket error" << endl;
        exit(-1);
    }
    cout << "sock: " << sock << "\nfileSock: " << fileSock << endl;
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

    sockaddr_in fileaddr;
    memset(&fileaddr, 0, sizeof(fileaddr));
    fileaddr.sin_family = AF_INET;
    fileaddr.sin_port = filePort;
    fileaddr.sin_addr.s_addr = addr;
    if (bind(fileSock, (sockaddr *)&fileaddr, sizeof(fileaddr)) == -1)
    {
        cout << "filesock bind error" << endl;
        exit(-1);
    }

    listen(sock, 10);
    listen(fileSock, 11);

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
    ev.events = EPOLLIN;
    ev.data.fd = fileSock;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fileSock, &ev) == -1)
    {
        cout << "add file epoll_fd error" << endl;
        exit(-1);
    }
}

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
            else if (ret_ev[i].data.fd == fileSock && (ret_ev[i].events & EPOLLIN))
            {
                int fileClient = accept(fileSock, NULL, NULL);
                if (fileClient == -1)
                {
                    cout << "accept error" << endl;
                    continue;
                }

                ev.events = EPOLLIN;
                ev.data.fd = fileClient;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fileClient, &ev);
                fileClient_fds.insert(fileClient);
                cout << "get a new fileClient" << endl;
            }
            else
            {
                //有客户端发送消息
                if (ret_ev[i].events & EPOLLIN)
                {
                    int in_fd = ret_ev[i].data.fd;
                    if (client_fds.find(in_fd) != client_fds.end())
                    {
                        int client = in_fd;
                        char buf[1024] = {0};
                        int bytes = recv(client, buf, 4, 0);
                        if (bytes == 0 || bytes == -1)
                        {
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
                        uint byten = bytes2uInt(buf);
                        cout << byten << " bytes received" << endl;
                        bytes = recv(client, buf, byten, 0);
                        cout << "recv = " << buf << endl;
                        handler.handle(client, buf, bytes);
                    }
                    else if (fileClient_fds.find(in_fd) != fileClient_fds.end())
                    {
                        int fileClient = in_fd;
                        char buf[5000] = {0};
                        int bytes = recv(fileClient, buf, 4, 0);
                        if (bytes == 0 || bytes == -1)
                        {
                            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fileClient, NULL);
                            fileClient_fds.erase(fileClient);
                            continue;
                        }
                        uint byten = bytes2uInt(buf);
                        cout << byten << " bytes received" << endl;
                        bytes = recv(fileClient, buf, byten, 0);
                        cout << "recvSize = " << bytes << endl;
                        handler.handle(fileClient, buf, bytes);
                    }
                    else if (fileOpened.find(in_fd) != fileOpened.end())
                    {
                        int fileFd = in_fd;
                        char buf[4096] = {0};
                        int bytes = read(fileFd, buf, 4096);
                        if (bytes == 0)
                        {
                            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fileFd, NULL);
                            fileOpened.erase(fileFd);
                            close(fileFd);
                            continue;
                        }
                        WriteFileTask out = fileSendTasks[fileFd];
                        int fileClient = out.fileFd;
                        sendStr(fileClient, buf, bytes);
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

void Server::sendFile(fd_t fileClient, std::string filepath)
{
    int fileFd = open(filepath.c_str(), O_RDONLY);
    if (fileFd == -1)
    {
        cout << "file open error" << endl;
    }
    fileOpened.insert(fileFd);
    WriteFileTask task;
    struct stat stFile;
    if ((fstat(fileFd, &stFile) == 0 && S_ISREG(stFile.st_mode)))
    {
        task.fileSize = stFile.st_size;
    }
    task.fileFd = fileClient;
    task.progress = 0;

    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fileClient;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fileFd, &ev);
    fileSendTasks[fileFd] = task;
}
