#include "messagerecord.h"

MessageRecord::MessageRecord()
{
}

MessageRecord::MessageRecord(std::vector<std::string> messages)
{
    record = messages;
}

void MessageRecord::push(std::string message)
{
    record.push_back(message);
}

void MessageRecord::remove(int index)
{
    record.erase(record.begin() + index);
}

std::vector<std::string> MessageRecord::getRecord()
{
    return record;
}
