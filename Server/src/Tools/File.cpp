#include "File.h"

using namespace std;

File::File(string filename)
{
    setName(filename);
}

std::string File::getName()
{
    return fileNameNoExtension + extension;
}

void File::setName(std::string filename)
{
    int pos = filename.find('.');
    if (pos == -1)
    {
        fileNameNoExtension = filename;
        extension = "";
    }
    else
    {
        fileNameNoExtension = filename.substr(0, pos);
        extension = filename.substr(pos);
    }
}