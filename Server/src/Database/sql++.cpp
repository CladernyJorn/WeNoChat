#include "sql++.h"
#include <iostream>
#include <sstream>

using namespace std;

Sql &Sql::singleton()
{
    static Sql instance;
    return instance;
}
void Sql::open()
{
    int status = sqlite3_open("res/database/info.db", &mySqlite);
    if (status != SQLITE_OK)
    {
        cout << "database open error" << endl;
    }
}

vector<UserRecord> Sql::findUserByName(string userName)
{
    string sql = "select * from User where username = " + userName;

    char **result = NULL;
    int nR = 0, nC = 0;
    char *errmsg = NULL;
    sqlite3_get_table(mySqlite, sql.c_str(), &result, &nR, &nC, &errmsg);

    string response;

    cout << nR << " users found" << endl;

    vector<UserRecord> recs;
    for (int i = 1; i <= nR; i++)
    {
        UserRecord rec;
        rec.username = string(result[i * nC + 0]);
        rec.password = string(result[i * nC + 1]);
        rec.phonenum = string(result[i * nC + 2]);
        sscanf(result[i * nC + 3], "%d", &rec.secureQue);
        rec.secureAns = string(result[i * nC + 4]);
        recs.push_back(rec);
    }
    return recs;
}

std::vector<std::string> Sql::findFriends(std::string userName)
{
    string sql = "select * from Friends where username = " + userName;

    char **result = NULL;
    int nR = 0, nC = 0;
    char *errmsg = NULL;
    sqlite3_get_table(mySqlite, sql.c_str(), &result, &nR, &nC, &errmsg);

    string response;

    cout << nR << " users found" << endl;

    vector<string> recs;
    for (int i = 1; i <= nR; i++)
    {
        recs.push_back(string(result[i * nC + 1]));
    }
    return recs;
}