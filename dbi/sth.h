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
	
	virtual ResultSet* Execute() = 0;
	virtual ResultSet* Execute(StatementArguments &args) = 0;
	virtual ResultSet* Execute(DBI::Any arg0);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8);
	virtual ResultSet* Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8, DBI::Any arg9);
};

}

#endif
