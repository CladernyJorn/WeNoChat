#include "CmdHandler.h"

using namespace std;

CmdHandler &CmdHandler::singleton()
{
    static CmdHandler singleton;
    return singleton;
}

CmdHandler::CmdHandler()
{
    __callbacks["login"] = __Callbacks::login;
    __callbacks["register"] = __Callbacks::regist;
}

void CmdHandler::handle(fd_t client, Json cmd)
{
    string name = cmd["data_type"];
    auto callback = __callbacks.find(name);
    if (callback != __callbacks.end())
        callback->second(client, cmd);
}

void __Callbacks::login(fd_t confd, Json cmd)
{
    // int type = 0;
    // char uName[512] = {0};
    // char pWord[1024] = {0};
    // sscanf(buf, "#|%d|%[^|]|%[^|]", &type, uName, pWord);

    // cout << type << '\n'
    //      << uName << '\n'
    //      << pWord << endl;

    // string sql = "select * from User where uName = " + string(uName);

    // char **result = NULL;
    // int nR = 0, nC = 0;
    // char *errmsg = NULL;
    // sqlite3_get_table(mySqlite, sql.c_str(), &result, &nR, &nC, &errmsg);

    // string response;

    // cout << nR << endl;

    // if (nR == 0)
    // {
    //     //用户不存在

    //     response = "#|1|1|用户不存在|&";
    //     send(confd, response.c_str(), response.length(), 0);
    //     return;
    // }
    // if (pWord == result[1])
    // {
    //     response = "#|1|0|登录成功|&";
    // }
    // else
    // {
    //     response = "#|1|0|密码错误|&";
    // }
    // send(confd, response.c_str(), response.length(), 0);
}

void __Callbacks::regist(fd_t client, Json cmd)
{
    // int type = 0;
    // char uName[32] = {0};
    // char pWord[32] = {0};
    // sscanf(buf, "#|%d|%[^|]|%[^|]", &type, uName, pWord);
    // char *errmsg = NULL;

    // cout << type << '\n'
    //      << uName << '\n'
    //      << pWord << endl;

    // string sqlStr = string("insert into User values('") + uName + "','" + pWord + "');";
    // cout << sqlStr << endl;
    // int sqlRet = sqlite3_exec(mySqlite, sqlStr.c_str(), NULL, NULL, &errmsg);
    // if (sqlRet != 0)
    // {
    //     cout << "sqlite3_error err: " << errmsg << endl;
    // }
}
