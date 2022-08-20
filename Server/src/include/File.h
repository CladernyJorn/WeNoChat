/**
 * 封装了文件的常用方法
 */

#ifndef __FILE_H__
#define __FILE_H__

#include "Constants.h"
#include <string>
#include <cstdlib>

class File
{
public:
    File(std::string fileName);
    std::string getName();
    void setName(std::string name);
    std::string fileNameNoExtension;
    std::string extension;
};

struct WriteFileTask
{
    fd_t fileFd;
    size_t fileSize;
    size_t progress;
};

#endif