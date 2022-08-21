#include "Tools.h"
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

int StrParser::toInt(string str)
{
    stringstream ss(str);
    int a;
    ss >> a;
    return a;
}

Json::Value makeCmd(std::string type, Json::Value cmd)
{
    Json::Value response;
    response["type"] = type;
    response["info"] = cmd;
    return response;
}

void sendJson(fd_t client, Json::Value json)
{
    string jsonStr = encodeJson(json);
    send(client, jsonStr.c_str(), jsonStr.length(), 0);
}