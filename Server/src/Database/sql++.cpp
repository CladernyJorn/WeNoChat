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
    int status = sqlite3_open("../res/database/info.db", &mySqlite);
    if (status != SQLITE_OK)
    {
        cout << "database open error" << endl;
    }
}

vector<UserRecord> Sql::findUserByName(string userName)
{
    string sql = "select * from User where uName = '" + userName + "';";

    cout << sql << endl;

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
        rec.headfile = string(result[i * nC + 5]);
        recs.push_back(rec);
    }
    return recs;
}

void Sql::insertUser(UserRecord rec)
{
    string sql = "insert into User values('" + rec.username + "', '" + rec.password + "', '" + rec.phonenum + "', " + to_string(rec.secureQue) + ", '" + rec.secureAns + "');";
    char *errmsg;
    int sqlRet = sqlite3_exec(mySqlite, sql.c_str(), NULL, NULL, &errmsg);
    if (sqlRet != 0)
    {
        cout << "sqlite3_error err: " << errmsg << endl;
    }
}

void Sql::updateUser(std::string username, std::string column, std::string value)
{
    string sql = "update User set " + column + " = '" + value + "' where uName = '" + username + "';";
    char *errmsg;
    int sqlRet = sqlite3_exec(mySqlite, sql.c_str(), NULL, NULL, &errmsg);
    if (sqlRet != 0)
    {
        cout << "sqlite3_error err: " << errmsg << endl;
    }
}

std::vector<UserRecord> Sql::findFriends(std::string userName)
{
    string sql = "select User.uName, head from Friends, User where Friends.username = '" + userName + "' and User.uName = Friends.friend;";

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
        rec.username = result[i * nC + 0];
        rec.headfile = result[i * nC + 1];
        recs.push_back(rec);
    }
    return recs;
}

void Sql::insertFriends(std::string user, std::string friend_user)
{
    string sql = "insert into Friends values('" + user + "', '" + friend_user + "');";
    char *errmsg;
    int sqlRet = sqlite3_exec(mySqlite, sql.c_str(), NULL, NULL, &errmsg);
    if (sqlRet != 0)
    {
        cout << "sqlite3_error err: " << errmsg << endl;
    }
}

void Sql::changeHeadFile(std::string user, std::string headFile)
{
    string sql = "update User set head = '" + headFile + "' where uName = '" + user + "';";
    char *errmsg;
    int sqlRet = sqlite3_exec(mySqlite, sql.c_str(), NULL, NULL, &errmsg);
    if (sqlRet != 0)
    {
        cout << "sqlite3_error err: " << errmsg << endl;
    }
}
