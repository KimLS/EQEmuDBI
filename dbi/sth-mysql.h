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
	
	virtual bool Execute();
	virtual bool Execute(StatementArguments &args);
	virtual ResultSet* Results();
private:
	MYSQL_STMT *statement;
};

}

#endif
