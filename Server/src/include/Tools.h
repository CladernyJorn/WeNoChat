/**
 * 工具类
 */

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <string>
#include <sstream>
#include <set>
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

// 向客户端发送json消息
void sendJson(fd_t client, Json::Value json);

/**
 * 编号生成器。
 * 从0开始生成序号，可以删除序号，下次生成会采用最小的未使用序号。
 * 复杂度O(log未使用的id个数)
 */

typedef unsigned long long idx_t;

#endif