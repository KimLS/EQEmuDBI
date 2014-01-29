#ifndef DBI__DBH_H
#define DBI__DBH_H

#include "dbi.h"

namespace DBI
{

//class DatabaseStatement;

enum DatabaseHandleErrorCode
{
	DBH_ERROR_NONE = 0,
	DBH_ERROR_INVALID_ARGS,
	DBH_ERROR_QUERY
};

class DBI_EXPORT DatabaseHandle
{
public:
	DatabaseHandle() { }
	virtual ~DatabaseHandle() { }
	
	virtual bool Connect(std::string dbname, std::string host, std::string username,
		std::string auth, DatabaseAttributes &attr) = 0;
	virtual bool Disconnect() = 0;
	
	virtual bool Do(std::string stmt) = 0;
	virtual bool Do(std::string stmt, StatementArguments &args) = 0;
	virtual bool Do(std::string stmt, DBI::Any arg0);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8);
	virtual bool Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8, DBI::Any arg9);

	//virtual DatabaseStatement* Prepare(std::string stmt) = 0;
	//virtual std::string Quote(std::string stmt) = 0;
	//
	//virtual bool BeginWork() = 0;
	//virtual bool Commit() = 0;
	//virtual bool Rollback() = 0;
	//
	
	bool Error() const { return error_code != DBH_ERROR_NONE; };
	const char* ErrorMessage() const { return error_message; }
	const DatabaseHandleErrorCode ErrorCode() const { return error_code; }
protected:
	void SetError(DatabaseHandleErrorCode code, const char *msg);
	char error_message[MAX_DBI_ERROR_MSG_LEN];
	DatabaseHandleErrorCode error_code;
};

}

#endif
