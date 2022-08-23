#include <sqlite3.h>
#include <cstdlib>
int main()
{
    sqlite3 *sql;
    int ret = sqlite3_open("./res/database/info.db", &sql);
    char *errmsg;
    sqlite3_exec(sql, "delete from User;", NULL, NULL, &errmsg);
    sqlite3_exec(sql, "delete from Friends;", NULL, NULL, &errmsg);
    system("rm -rf ./res/users/*");
    return 0;
}