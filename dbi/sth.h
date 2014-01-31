#ifndef DBI__STH_H
#define DBI__STH_H

#include "dbi.h"
#include "dbi-error.h"

namespace DBI
{

class ResultSet;

class StatementHandle : public ErrorHandler
{
public:
	StatementHandle() { }
	virtual ~StatementHandle() { }
	
	virtual std::unique_ptr<ResultSet> Execute() = 0;
	virtual std::unique_ptr<ResultSet> Execute(StatementArguments &args) = 0;
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8);
	virtual std::unique_ptr<ResultSet> Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8, DBI::Any arg9);
};

}

#endif
