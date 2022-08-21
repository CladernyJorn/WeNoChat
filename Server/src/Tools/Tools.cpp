#include "Tools.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <fstream>
#include <sstream>

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

std::string readFile(std::string filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        return "";
    }
    stringstream ss;
    ss << fin.rdbuf();
    return ss.str();
}