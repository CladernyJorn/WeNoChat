#include "CmdHandler.h"
#include "sql++.h"
#include "Server.h"

#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
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
    __callbacks["findpWord1"] = __Callbacks::_findPword_phone;
    __callbacks["findpWord2"] = __Callbacks::_findPword_que;
    __callbacks["findpWord3"] = __Callbacks::_findPword_change;
    __callbacks["sendFile"] = __Callbacks::_sendFile;
    __callbacks["updateFile"] = __Callbacks::_updateFile;
    __callbacks["sendOver"] = __Callbacks::_sendOver;
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
    mkdir((user_path + uName).c_str(), S_IRWXU);
    sendJson(client, makeCmd("regist", response));
}

void __Callbacks::_chat(fd_t client, Json::Value cmd)
{
    string _from = cmd["username"].asString();
    Json::Value _to = cmd["userList"];
    string _msg = cmd["info"].asString();

    cout << "msg from " << _from << " to " << encodeJson(_to) << ": " << _msg << endl;

    int len = _to.size();
    for (int i = 0; i < len; i++)
    {
        Json::Value response;
        response["username"] = _from;
        response["info"] = _msg;
        string userName = _to[i].asString();
        fd_t tgtfd = Server::singleton().getFdByName(userName);
        cout << "tgtfd = " << tgtfd << endl;
        cout << "client = " << client << endl;
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

    vector<UserRecord> user = Sql::singleton().findUserByName(friendUser);
    Json::Value response;
    if (user.size() != 0)
    {
        response["state"] = 1;
        response["username"] = friendUser;
        sendJson(client, makeCmd("addfriends", response));
        fd_t friend_fd = Server::singleton().getFdByName(friendUser);
        response["state"] = 1;
        response["username"] = username;
        sendJson(friend_fd, makeCmd("addfriends", response));

        Sql::singleton().insertFriends(username, friendUser);
        Sql::singleton().insertFriends(friendUser, username);
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
            CmdHandler::singleton().pWordForgotters[username] = recs[0];
        }
    }
    sendJson(client, makeCmd("findpWord1", response));
}

void __Callbacks::_findPword_que(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string secureA = cmd["secureAns"].asString();
    CmdHandler &handler = CmdHandler::singleton();
    auto ur = handler.pWordForgotters.find(username);

    Json::Value response;
    response["username"] = username;
    if (ur != handler.pWordForgotters.end())
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
    auto ur = handler.pWordForgotters.find(username);

    Json::Value response;
    response["username"] = username;
    if (ur != handler.pWordForgotters.end())
    {
        Sql::singleton().updateUser(username, "pWord", newpWord);
        handler.pWordForgotters.erase(ur);
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
    handler.pWordForgotters.erase(username);
}

void __Callbacks::_sendFile(fd_t client, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string fileName = cmd["fileName"].asString();
    unsigned long long fileSize = cmd["fileSize"].asUInt64();
    string user_dir = user_path + username + "/";
    File file(fileName);
    string file_path = user_dir + file.getName();
    Json::Value response;
    fd_t fileFd;
    CmdHandler &handler = CmdHandler::singleton();
    if (access((file_path).c_str(), F_OK) != 0)
    {
        fileFd = creat(file_path.c_str(), S_IRWXU);
    }
    else
    {
        string tmpname;
        for (int i = 1;; i++)
        {
            tmpname = file.fileNameNoExtension + "(" + to_string(i) + ")";
            if (access((tmpname + file.extension).c_str(), F_OK) != 0)
                break;
        }
        file.fileNameNoExtension = tmpname;
        file_path = user_dir + file.getName();
        fileFd = creat(file_path.c_str(), S_IRWXU);
    }
    response["fileFd"] = fileFd;
    WriteFileTask task;
    task.fileSize = fileSize;
    task.progress = 0;
    handler.fileTasks[fileFd] = task;
    sendJson(client, makeCmd("confirmSendFile", response));
}

void __Callbacks::_updateFile(fd_t client, Json::Value cmd)
{
    idx_t fileFd = cmd["fileFd"].asUInt64();
    int size = cmd["size"].asInt();
    const char *bytes = cmd["Bytes"].asCString();
    CmdHandler &handler = CmdHandler::singleton();
    auto p_id = handler.fileTasks.find(fileFd);
    if (p_id != handler.fileTasks.end())
    {
        WriteFileTask task = p_id->second;
        int written = write(fileFd, bytes, size);
        task.progress += written;
    }
}

void __Callbacks::_sendOver(fd_t client, Json::Value cmd)
{
    idx_t fileFd = cmd["fileFd"].asUInt64();
    CmdHandler &handler = CmdHandler::singleton();
    auto p_id = handler.fileTasks.find(fileFd);
    Json::Value response;
    if (p_id != handler.fileTasks.end())
    {
        WriteFileTask task = p_id->second;
        if (task.progress == task.fileSize)
            response["state"] = 1;
        else
            response["state"] = 0;
        handler.fileTasks.erase(p_id);
    }
    sendJson(client, makeCmd("sendState", response));
}
