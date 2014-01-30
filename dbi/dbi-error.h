#ifndef DBI__DBI_ERROR_H
#define DBI__DBI_ERROR_H

#include <string>

namespace DBI
{

enum DBIErrorCode
{
	DBI_ERROR_NONE = 0,
	DBI_ERROR_DRIVER_NOT_FOUND,
	DBI_ERROR_FAILED_TO_CONNECT,
	DBH_ERROR_INVALID_ARGS,
	DBH_ERROR_QUERY,
	DBH_ERROR_BIND_FAILURE,
	DBH_ERROR_STMT_FAILURE,
	DBH_ERROR_PREPARE_FAILURE,
	STH_ERROR_INVALID_ARGS,
	STH_ERROR_BIND_FAILURE,
	STH_ERROR_STMT_FAILURE
};

class ErrorHandler
{
public:
	ErrorHandler() { }
	virtual ~ErrorHandler() { }
	
	bool Error() const { return error_code != DBI_ERROR_NONE; };
	std::string ErrorMessage() const { return error_message; }
	const DBIErrorCode ErrorCode() const { return error_code; }
protected:
	void SetError(DBIErrorCode code, std::string msg);
	std::string error_message;
	DBIErrorCode error_code;
};

}

#endif
