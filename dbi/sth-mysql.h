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
	
	virtual ResultSet* Execute();
	virtual ResultSet* Execute(StatementArguments &args);
private:
	MYSQL_STMT *statement;
};

}

#endif
