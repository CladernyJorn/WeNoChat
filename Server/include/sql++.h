/**
 * 将sqlite3封装后的类。
 */

#ifndef __SQLXX_H__
#define __SQLXX_H__

#include <sqlite3.h>
#include <string>

#include "Record.h"

typedef UserRecord UserAccountRecord;

class Sql
{
public:
    UserRecord findUserByName(std::string userName);
    void insertUser(UserAccountRecord);

private:
    sqlite3 *mySqlite;
};

#endif