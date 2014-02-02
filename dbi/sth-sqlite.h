#ifndef DBI__STH_SQLITE_H
#define DBI__STH_SQLITE_H

#include "sth.h"
#include "dbh-sqlite.h"

namespace DBI
{

class ResultSet;

class SQLiteStatementHandle : public StatementHandle
{
public:
	SQLiteStatementHandle(sqlite3 *handle_, sqlite3_stmt *stmt_);
	virtual ~SQLiteStatementHandle();
	
	virtual std::unique_ptr<ResultSet> Execute();
	virtual std::unique_ptr<ResultSet> Execute(StatementArguments &args);
private:
	sqlite3 *handle;
	sqlite3_stmt *stmt;
};

}

#endif
