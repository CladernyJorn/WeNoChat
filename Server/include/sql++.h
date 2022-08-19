/**
 * 将sqlite3封装后的类。
 */

#ifndef __SQLXX_H__
#define __SQLXX_H__

#include <sqlite3.h>
#include <string>

class Sql
{
public:
    int getTable(sqlite3 *pSql, const char *sql, char ***result, int *nR, int *nC, char **errmsg);
    int open(const char *path);
    int exec(sqlite3 *pSql, const char *sql, int (*callback)(void *, int, char **, char **), void *, char **errmsg);

private:
    sqlite3 *mySqlite;
};

#endif