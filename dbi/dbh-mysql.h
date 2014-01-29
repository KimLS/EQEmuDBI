#ifndef DBI__DBH_MYSQL_H
#define DBI__DBH_MYSQL_H

#include "dbh.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>

namespace DBI
{
//class DatabaseStatement;

class DBI_EXPORT MySQLDatabaseHandle : public DatabaseHandle
{
public:
	MySQLDatabaseHandle();
	virtual ~MySQLDatabaseHandle();
	
	virtual bool Connect(std::string dbname, std::string host, std::string username,
		std::string auth, DatabaseAttributes &attr);
	virtual bool Disconnect();
	
	virtual bool Do(std::string stmt);
	virtual bool Do(std::string stmt, StatementArguments &args);
	//virtual DatabaseStatement* Prepare(std::string stmt) = 0;
	//virtual std::string Quote(std::string stmt) = 0;
	//
	//virtual bool BeginWork() = 0;
	//virtual bool Commit() = 0;
	//virtual bool Rollback() = 0;

private:
	bool _basic_execute(std::string stmt, StatementArguments &args);
	bool _basic_execute_server_side(std::string stmt, StatementArguments &args);
	std::string _quote(std::string v);
	MYSQL *handle;
	bool server_side_prepare;
};

}

#endif
