#ifndef DBI__STH_MYSQL_H
#define DBI__STH_MYSQL_H

#include "sth.h"
#include "dbh-mysql.h"

struct st_mysql_stmt;
typedef struct st_mysql_stmt MYSQL_STMT;

namespace DBI
{

class ResultSet;

class MySQLStatementHandle : public StatementHandle
{
public:
	MySQLStatementHandle(MYSQL_STMT *stmt);
	virtual ~MySQLStatementHandle();
	
	virtual std::unique_ptr<ResultSet> Execute();
	virtual std::unique_ptr<ResultSet> Execute(StatementArguments &args);
private:
	MYSQL_STMT *statement;
};

}

#endif
