#ifndef __CMD_HANDLER_H__
#define __CMD_HANDLER_H__

#include <unordered_map>
#include <string>
#include <functional>

#include "Constants.h"

#include "Json.h"

class CmdHandler
{
public:
    static CmdHandler &singleton();
    void handle(fd_t client, Json::Value cmd);

private:
    CmdHandler();
    CmdHandler(const CmdHandler &) = delete;
    CmdHandler &operator=(const CmdHandler &) = delete;
    std::unordered_map<std::string, std::function<void(fd_t client, Json::Value cmd)>> __callbacks;
};

namespace __Callbacks
{
    void _login(fd_t confd, Json::Value cmd);
    void _register(fd_t client, Json::Value cmd);
    void _chat(fd_t client, Json::Value cmd);
    void _getFriends(fd_t client, Json::Value cmd);
    void _addFriends(fd_t client, Json::Value cmd);
}
#endif // CmdHandler.h