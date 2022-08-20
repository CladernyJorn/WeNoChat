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

idx_t IndexGenerator::getIdx()
{
    if (idxs.empty())
        return max_id++;
    else
    {
        auto it_idx = idxs.begin();
        idx_t idx = *it_idx;
        idxs.erase(it_idx);
        return idx;
    }
}
void IndexGenerator::popIdx(idx_t idx)
{
    if (idx == max_id)
        max_id--;
    else
        idxs.insert(idx);
}