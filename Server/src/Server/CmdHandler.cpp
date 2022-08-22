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
    __callbacks["rqirFile"] = __Callbacks::_rqirFile;
}

void CmdHandler::handle(fd_t client, const char *buf, int _n)
{
    Json::Value cmd = decodeJson(buf);
    if (cmd.isObject())
    {
        if (cmd.isMember("type") && cmd.isMember("info"))
        {
            string name = cmd["type"].asString();
            auto callback = __callbacks.find(name);
            if (callback != __callbacks.end())
                callback->second(client, cmd["info"]);
        }
    }
    else
    {
        __Callbacks::_updateFile(client, buf, _n);
    }
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
        Server::singleton().addClient(uName, client);
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
        if (friend_fd != 0)
        {
            response["state"] = 1;
            response["username"] = username;
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

void __Callbacks::_sendFile(fd_t fileClient, Json::Value cmd)
{
    string username = cmd["username"].asString();
    string fileName = cmd["fileName"].asString();
    unsigned long long fileSize = cmd["size"].asUInt64();
    cout << username << " send a file " << fileName << " with size " << fileSize << endl;
    string user_dir = user_path + username + "/";
    string file_path = user_dir + fileName;
    File file(file_path);
    Json::Value response;
    fd_t fileFd;
    CmdHandler &handler = CmdHandler::singleton();
    if (access((file_path).c_str(), F_OK) != 0)
    {
        cout << "no such file" << endl;
        fileFd = open(file_path.c_str(), O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, S_IRWXU);
        if (fileFd == -1)
        {
            cout << "file create failed" << endl;
        }
    }
    else
    {
        cout << "file name exists" << endl;
        string tmpname;
        for (int i = 1;; i++)
        {
            tmpname = file.fileNameNoExtension + "(" + to_string(i) + ")";
            if (access((file.directory + tmpname + file.extension).c_str(), F_OK) != 0)
                break;
        }
        file.fileNameNoExtension = tmpname;
        fileFd = open(file_path.c_str(), O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, S_IRWXU);
        if (fileFd == -1)
        {
            cout << "file create failed" << endl;
        }
    }
    WriteFileTask task;
    task.fileFd = fileFd;
    task.fileSize = fileSize;
    task.progress = 0;
    handler.fileTasks[fileClient] = task;
}

void __Callbacks::_updateFile(fd_t fileClient, const char *buf, int _n)
{
    CmdHandler &handler = CmdHandler::singleton();
    auto p_id = handler.fileTasks.find(fileClient);
    if (p_id != handler.fileTasks.end())
    {
        WriteFileTask *task = &p_id->second;
        int written = write(task->fileFd, buf, _n);
        cout << "written: " << written << endl;
        task->progress += written;
        cout << "progress: " << task->progress << endl;
        if (task->progress == task->fileSize)
        {
            Json::Value response;
            response["state"] = 1;
            handler.fileTasks.erase(p_id);
            sendJson(fileClient, makeCmd("sendState", response));
            close(task->fileFd);
        }
    }
}

void __Callbacks::_rqirFile(fd_t fileClient, Json::Value cmd)
{
    File file(cmd["fileName"].asString());
    Json::Value response;
}
