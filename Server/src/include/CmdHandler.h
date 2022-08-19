#ifndef __CMD_HANDLER_H__
#define __CMD_HANDLER_H__

#include <unordered_map>
#include <string>
#include <functional>

#include "Constants.h"

//下面两行用来占位
#include <map>
typedef std::map<std::string, std::string> Json;

class CmdHandler
{
public:
    static CmdHandler &singleton();
    void handle(fd_t client, Json cmd);

private:
    CmdHandler();
    CmdHandler(const CmdHandler &) = delete;
    CmdHandler &operator=(const CmdHandler &) = delete;
    std::unordered_map<std::string, std::function<void(fd_t client, Json cmd)>> __callbacks;
};

namespace __Callbacks
{
    void login(fd_t confd, Json cmd);
    void regist(fd_t client, Json cmd);
}
#endif // CmdHandler.h