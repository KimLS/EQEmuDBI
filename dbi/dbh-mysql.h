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

ResultSet* _internal_results_from_mysql_stmt(MYSQL_STMT* statement);

class MySQLDatabaseHandle : public DatabaseHandle
{
public:
	MySQLDatabaseHandle();
	virtual ~MySQLDatabaseHandle();
	
	virtual bool Connect(std::string dbname, std::string host, std::string username,
		std::string auth, DatabaseAttributes &attr);
	virtual bool Disconnect();
	
	virtual ResultSet* Do(std::string stmt);
	virtual ResultSet* Do(std::string stmt, StatementArguments &args);
	virtual StatementHandle* Prepare(std::string stmt);

	virtual bool Ping();
	virtual bool Begin();
	virtual bool Commit();
	virtual bool Rollback();

private:
	ResultSet* _basic_execute_server_side(std::string stmt, StatementArguments &args);
	MYSQL *handle;
};

}

#endif
