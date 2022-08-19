#include <iostream>
#include <cstdio>
#include <sqlite3.h>
using namespace std;
struct Table
{
	char **data;
	int rowNum, columnNum;
};
class Database
{
public:
	Database(char* databaseName);
	~Database();
	int executeSQL(char* sql);
	int getTable(char* sql, Table &table);
private:
	sqlite3 *database;
};
Database::Database(char* databaseName)
{
	int open_state = sqlite3_open(databaseName, &database);
	if (open_state != 0)
	{
		cout << "failed to open sqlite3."<< endl;
		exit(-1);
	}
}
Database::~Database()
{
	sqlite3_close(database);
}
int Database::executeSQL(char *sql)
{
	char *errmsg = NULL;
	int sqlRet = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
	if(sqlRet != 0)
	{
		printf("sql execution failed, message: %s\n", errmsg);
		return false;
	}
	return true;
}
int Database::getTable(char *sql, Table &table)
{
	char *errmsg = NULL;
	int sqlRet = sqlite3_get_table(database, sql, &table.data, &table.rowNum, &table.columnNum, &errmsg);
	if (sqlRet != 0)
	{
		printf("get_table error message: %s\n", errmsg);
		return false;
	}
	return true;
}
