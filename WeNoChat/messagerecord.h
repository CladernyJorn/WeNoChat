#ifndef MESSAGERECORD_H
#define MESSAGERECORD_H

#include <string>
#include <vector>

class MessageRecord
{
public:
    MessageRecord();
    MessageRecord(std::vector<std::string> messages);
    void appendMessage(std::string message);
    void deleteMessage(int index);
    std::vector<std::string> getAllMessageRecord();

private:
    std::vector<std::string> record;
};

#endif // MESSAGERECORD_H
