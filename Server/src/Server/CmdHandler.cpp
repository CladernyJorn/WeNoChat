#include "CmdHandler.h"
#include "sql++.h"
#include "Record.h"
#include "Tools.h"
#include "Server.h"

#include <iostream>
#include <vector>

using namespace std;

CmdHandler &CmdHandler::singleton()
{
    static CmdHandler singleton;
    return singleton;
}

CmdHandler::CmdHandler()
{
    __callbacks["login"] = __Callbacks::_login;
    __callbacks["regist"] = __Callbacks::_register;
    __callbacks["chat"] = __Callbacks::_chat;
    __callbacks["askfriendsList"] = __Callbacks::_getFriends;
    __callbacks["addfriends"] = __Callbacks::_addFriends;
}

void CmdHandler::handle(fd_t client, Json::Value cmd)
{
    string name = cmd["type"].asString();
    auto callback = __callbacks.find(name);
    if (callback != __callbacks.end())
        callback->second(client, cmd["info"]);
}

void __Callbacks::_login(fd_t client, Json::Value cmd)
{
    string uName = cmd["username"].asString();
    string pWord = cmd["password"].asString();

    cout << "login: " << uName << ' ' << pWord << endl;

    vector<UserRecord> users = Sql::singleton().findUserByName(uName);

    Json::Value response;

    if (users.size() == 0)
    {
        response["state"] = 0;
        response["info"] = "用户不存在";
    }
    else if (pWord == users[0].password)
    {
        response["state"] = 1;
        response["info"] = "登录成功";
        Server::singleton().addClient(uName, client);
    }
    else
    {
        response["state"] = 0;
        response["info"] = "密码错误";
    }
    sendJson(client, makeCmd("login", response));
}

void __Callbacks::_register(fd_t client, Json::Value cmd)
{
    string uName = cmd["username"].asString();
    string pWord = cmd["password"].asString();
    string phone = cmd["phonenum"].asString();
    int secureQ = cmd["secureQue"].asInt();
    string secureA = cmd["secureAns"].asString();

    cout << "register: " << uName << ' ' << pWord << endl;

    vector<UserRecord> users = Sql::singleton().findUserByName(uName);

    Json::Value response;
    if (users.size() != 0)
    {
        response["state"] = 0;
        response["info"] = "用户名已存在！";
    }
    else
    {
        UserRecord rec = {uName,
                          pWord,
                          phone,
                          secureQ,
                          secureA};
        Sql::singleton().insertUser(rec);
        response["state"] = 1;
        response["info"] = "注册成功！";
    }
    sendJson(client, makeCmd("regist", response));
}

void __Callbacks::_chat(fd_t client, Json::Value cmd)
{
    string _from = cmd["username"].asString();
    Json::Value _to = cmd["userList"];
    string _msg = cmd["msg"].asString();

    cout << "msg from " << _from << " to " << encodeJson(_to) << ": " << _msg << endl;

    // TODO: 找到接收方，发送该信息。
    int len = _to.size();
    for (int i = 0; i < len; i++)
    {
        Json::Value response;
        response["username"] = _from;
        response["info"] = _msg;
        string userName = _to[i].asString();
        fd_t tgtfd = Server::singleton().getFdByName(userName);
        sendJson(tgtfd, makeCmd("chat", response));
    }
}

void __Callbacks::_getFriends(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    cout << username << "getfriends" << endl;
    vector<string> friends = Sql::singleton().findFriends(username);
    Json::Value response;
    response["username"] = username;
    for (int i = 0; i < (int)friends.size(); i++)
    {
        response["userList"][i] = friends[i];
    }
    sendJson(client, makeCmd("askfriendsList", response));
}

void __Callbacks::_addFriends(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string friendUser = cmd["friend_username"].asString();

    cout << username << "wants to make friends with " << friendUser << endl;
}