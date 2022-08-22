#include "CmdHandler.h"
#include "sql++.h"
#include "Tools.h"
#include "Server.h"

#include <iostream>
#include <fstream>
#include <sstream>
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
    __callbacks["findpWord1"] = __Callbacks::_findPword_phone;
    __callbacks["findpWord2"] = __Callbacks::_findPword_que;
    __callbacks["findpWord3"] = __Callbacks::_findPword_change;
    __callbacks["submit_image"] = __Callbacks::_submitImage;
    __callbacks["inform_chatfile"] = __Callbacks::_informChatFile;
    __callbacks["chatfile"] = __Callbacks::_chatFile;
    __callbacks["inform_submit_image"] = __Callbacks::_informSubmitImage;
}

void CmdHandler::handle(fd_t client, std::string buf)
{
    Json::Value cmd;
    // decodeJson(buf);
    Json::Reader reader;
    CmdHandler &handler = CmdHandler::singleton();
    auto ptmpCmd = handler.tmpCmds.find(client);
    if (ptmpCmd != handler.tmpCmds.end())
    {
        handler.tmpCmds[client] = string();
    }
    string &tmpCmd = handler.tmpCmds[client];
    tmpCmd.append(buf);
    cout << tmpCmd << endl;
    if (!reader.parse(tmpCmd, cmd))
    {
        return;
    }
    if (!cmd.isObject())
    {
        return;
    }
    tmpCmd.clear();
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
    response["username"] = uName;

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
    response["username"] = uName;
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
                          secureA, ""};
        Sql::singleton().insertUser(rec);
        response["state"] = 1;
        response["info"] = "注册成功！";

        Server::singleton().addClient(uName, client);
    }
    sendJson(client, makeCmd("regist", response));
}

void __Callbacks::_chat(fd_t client, Json::Value cmd)
{
    string _from = cmd["username"].asString();
    Json::Value _to = cmd["userList"];
    string _msg = cmd["info"].asString();

    cout << "msg from " << _from << " to " << encodeJson(_to) << ": " << _msg << endl;

    int len = _to.size();
    cout << "len " << len << endl;
    for (int i = 0; i < len; i++)
    {
        Json::Value response;
        response["username"] = _from;
        response["info"] = _msg;
        string userName = _to[i].asString();
        fd_t tgtfd = Server::singleton().getFdByName(userName);
        cout << "tgtfd " << tgtfd << endl;
        if (tgtfd != -1)
        {
            cout << "tgtfd = " << tgtfd << endl;
            cout << "client = " << client << endl;
            sendJson(tgtfd, makeCmd("chat", response));
        }
    }
}

void __Callbacks::_getFriends(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    cout << username << "getfriends" << endl;
    vector<UserRecord> friends = Sql::singleton().findFriends(username);

    cout << username << endl;
    vector<UserRecord> me = Sql::singleton().findUserByName(username);
    Json::Value response;
    response["username"] = username;
    response["user_image"] = me[0].headfile;
    for (int i = 0; i < (int)friends.size(); i++)
    {
        Json::Value user_info;
        user_info["friend_name"] = friends[i].username;
        user_info["friend_image"] = friends[i].headfile;
        response["user_info_List"][i] = user_info;
    }
    cout << encodeJson(response) << endl;
    sendJson(client, makeCmd("askfriendsList", response));
}

void __Callbacks::_addFriends(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string friendUser = cmd["friend_username"].asString();

    cout << username << "wants to make friends with " << friendUser << endl;

    vector<UserRecord> user = Sql::singleton().findUserByName(friendUser);
    vector<UserRecord> me = Sql::singleton().findUserByName(username);
    Json::Value response;

    if (user.size() != 0)
    {
        response["state"] = 1;
        response["username"] = friendUser;
        response["user_image"] = user[0].headfile;

        sendJson(client, makeCmd("addfriends", response));
        fd_t friend_fd = Server::singleton().getFdByName(friendUser);
        if (friend_fd != 0)
        {
            response["state"] = 1;
            response["username"] = username;
            response["user_image"] = me[0].headfile;
            sendJson(friend_fd, makeCmd("addfriends", response));
        }

        Sql::singleton().insertFriends(username, friendUser);
    }
    else
    {
        response["state"] = 0;
        response["username"] = "";
        sendJson(client, makeCmd("addfriends", response));
    }
}

void __Callbacks::_findPword_phone(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string phonenum = cmd["phonenum"].asString();

    Sql &sql = Sql::singleton();
    vector<UserRecord> recs = sql.findUserByName(username);
    Json::Value response;
    response["username"] = username;
    if (recs.size() == 0)
    {
        response["state"] = 0;
        response["info"] = "用户不存在";
        response["secureQue"] = 0;
    }
    else
    {
        if (recs[0].phonenum != phonenum)
        {
            response["state"] = 0;
            response["info"] = "电话号码错误";
            response["secureQue"] = 0;
        }
        else
        {
            response["state"] = 1;
            response["secureQue"] = recs[0].secureQue;
            response["info"] = "";
            CmdHandler::singleton().getpWordForgotter()[username] = recs[0];
        }
    }
    sendJson(client, makeCmd("findpWord1", response));
}

void __Callbacks::_findPword_que(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string secureA = cmd["secureAns"].asString();
    CmdHandler &handler = CmdHandler::singleton();
    unordered_map<string, UserRecord> &forgotter = handler.getpWordForgotter();
    auto ur = forgotter.find(username);

    Json::Value response;
    response["username"] = username;
    if (ur != forgotter.end())
    {
        if (secureA == ur->second.secureAns)
            response["state"] = 1;
        else
            response["state"] = 0;
    }
    else
    {
        response["state"] = 0;
    }
    sendJson(client, makeCmd("findpWord2", response));
}

void __Callbacks::_findPword_change(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string newpWord = cmd["newpWord"].asString();
    CmdHandler &handler = CmdHandler::singleton();
    unordered_map<string, UserRecord> &forgotter = handler.getpWordForgotter();
    auto ur = forgotter.find(username);

    Json::Value response;
    response["username"] = username;
    if (ur != forgotter.end())
    {
        Sql::singleton().updateUser(username, "pWord", newpWord);
        forgotter.erase(ur);
        response["state"] = 1;
    }
    else
    {
        response["state"] = 0;
    }
    sendJson(client, makeCmd("findpWord3", response));
}

void __Callbacks::_cancelFindPword(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    CmdHandler &handler = CmdHandler::singleton();
    unordered_map<string, UserRecord> &forgotter = handler.getpWordForgotter();
    forgotter.erase(username);
}

void __Callbacks::_submitImage(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string image_buf = cmd["image"].asString();
    cout << "username = " << username << endl;
    cout << "imagesize = " << image_buf.length() << endl;
    Sql::singleton().changeHeadFile(username, image_buf);
    Json::Value response;
    response["username"] = username;
    response["state"] = 1;
    sendJson(client, makeCmd("submit_image", response));
}

unordered_map<string, UserRecord> &CmdHandler::getpWordForgotter()
{
    return pWordForgotters;
}

void __Callbacks::_informChatFile(fd_t client, Json::Value cmd)
{
    string fileName = cmd["filename"].asString();
    string username = cmd["username"].asString();
    int size = cmd["size"].asInt();
    Json::Value response;
    response["state"] = 1;
    sendJson(client, makeCmd("ready_chatfile", response));
}
void __Callbacks::_chatFile(fd_t client, Json::Value cmd)
{
    string fileName = cmd["filename"].asString();
    Json::Value userList = cmd["userList"];
    string username = cmd["username"].asString();
    Json::Value info = cmd["info"];

    cout << "file from " << username << " to " << encodeJson(userList) << endl;

    for (int i = 0; i < userList.size(); i++)
    {
        string uName = userList[i].asString();
        int fd;
        if ((fd = Server::singleton().getFdByName(uName)) == -1)
            return;

        Json::Value response;
        response["filename"] = fileName;
        response["username"] = username;
        response["info"] = info;
        sendJson(fd, makeCmd("chatfile", response));
    }
}
void __Callbacks::_informSubmitImage(fd_t client, Json::Value cmd)
{
    string fileName = cmd["filename"].asString();
    string username = cmd["username"].asString();
    int size = cmd["size"].asInt();

    int pos = fileName.find_last_of('.');
    string ex = fileName.substr(pos);

    Json::Value response;
    response["state"] = 1;

    sendJson(client, makeCmd("ready_submit_image", response));
}