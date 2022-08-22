#include "messagerecord.h"

MessageRecord::MessageRecord(std::vector<std::string> messages)
{
    record = messages;
}

void MessageRecord::appendMessage(std::string message)
{
    record.push_back(message);
}

void MessageRecord::deleteMessage(int index)
{
    record.erase(record.begin() + index);
}

std::vector<std::string> MessageRecord::getAllMessageRecord()
{
    return record;
}
