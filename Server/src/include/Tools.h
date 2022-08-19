/**
 * 工具类
 */

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <string>
#include <sstream>
#include "Json.h"
#include "Constants.h"

namespace StrParser
{
    /**
     * @brief 转换字符串为int
     */
    int toInt(std::string);
}

// 打包发回客户端的信息
Json::Value makeCmd(std::string type, Json::Value cmd);

void sendJson(fd_t client, Json::Value json);
#endif