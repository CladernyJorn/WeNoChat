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

class Sql
{
public:
    static Sql &singleton();

    void open();
    std::vector<UserRecord> findUserByName(std::string userName);
    void insertUser(UserRecord rec);
    void updateUser(std::string username, std::string column, std::string value);
    std::vector<UserRecord> findFriends(std::string userName);
    void insertFriends(std::string user, std::string friend_user);
    void changeHeadFile(std::string user, std::string headFile);

private:
    Sql() {}
    Sql(const Sql &) = delete;
    Sql &operator=(const Sql &) = delete;
    sqlite3 *mySqlite;
};

#endif