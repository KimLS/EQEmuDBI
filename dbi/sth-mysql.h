#ifndef DBI__STH_MYSQL_H
#define DBI__STH_MYSQL_H

#include "sth.h"
#include "dbh-mysql.h"

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
	struct STMTHandle;
	STMTHandle *statement;
};

}

#endif
