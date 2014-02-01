#ifndef DBI__DBH_SQLITE_H
#define DBI__DBH_SQLITE_H

#include "dbh.h"
#include "sqlite3.h"

namespace DBI
{

class SQLiteDatabaseHandle : public DatabaseHandle
{
public:
	SQLiteDatabaseHandle();
	virtual ~SQLiteDatabaseHandle();
	
	virtual bool Connect(std::string dbname, std::string host, std::string username,
		std::string auth, DatabaseAttributes &attr);
	virtual bool Disconnect();
	
	virtual std::unique_ptr<ResultSet> Do(std::string stmt);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, StatementArguments &args);
	virtual std::unique_ptr<StatementHandle> Prepare(std::string stmt);

	virtual bool Ping();
	virtual bool Begin();
	virtual bool Commit();
	virtual bool Rollback();

private:
	sqlite3 *handle;
};

}

#endif
