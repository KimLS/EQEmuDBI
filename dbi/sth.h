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
	
	virtual bool Execute() = 0;
	virtual bool Execute(StatementArguments &args) = 0;
	virtual bool Execute(DBI::Any arg0);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8);
	virtual bool Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8, DBI::Any arg9);

	virtual ResultSet* Results() = 0;
};

}

#endif
