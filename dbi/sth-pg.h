#ifndef DBI__STH_PG_H
#define DBI__STH_PG_H

#include "sth.h"
#include "dbh-pg.h"

struct pg_conn;
typedef struct pg_conn PGconn;

namespace DBI
{

class ResultSet;

class PGStatementHandle : public StatementHandle
{
public:
	PGStatementHandle(PGconn *conn_, std::string name_);
	virtual ~PGStatementHandle();
	
	virtual std::unique_ptr<ResultSet> Execute();
	virtual std::unique_ptr<ResultSet> Execute(StatementArguments &args);
private:
	PGconn *conn;
	std::string name;
};

}

#endif
