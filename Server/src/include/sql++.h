/**
 * 将sqlite3封装后的类。
 */

#ifndef __SQLXX_H__
#define __SQLXX_H__

#include <sqlite3.h>
#include <vector>
#include <string>

#include "Record.h"
#include "Tools.h"

typedef UserRecord UserAccountRecord;

class Sql
{
public:
    static Sql &singleton();

    void open();
    std::vector<UserRecord> findUserByName(std::string userName);
    void insertUser(UserAccountRecord rec);
    std::vector<std::string> findFriends(std::string userName);

private:
    Sql() {}
    Sql(const Sql &) = delete;
    Sql &operator=(const Sql &) = delete;
    sqlite3 *mySqlite;
};

#endif