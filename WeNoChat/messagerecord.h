#ifndef MESSAGERECORD_H
#define MESSAGERECORD_H

#include <string>
#include <vector>

class MessageRecord
{
public:
    MessageRecord();
    MessageRecord(std::vector<std::string> messages);
    void push(std::string message);
    void remove(int index);
    std::vector<std::string> getRecord();

private:
    std::vector<std::string> record;
};

#endif // MESSAGERECORD_H
