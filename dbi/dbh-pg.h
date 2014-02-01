#ifndef DBI__DBH_PGL_H
#define DBI__DBH_PGL_H

#include "dbh.h"
#include <libpq-fe.h>

namespace DBI
{

std::unique_ptr<ResultSet> _internal_results_from_postgresql(PGresult* res);

class PGDatabaseHandle : public DatabaseHandle
{
public:
	PGDatabaseHandle();
	virtual ~PGDatabaseHandle();
	
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
	std::string _process_query(std::string stmt, int *params = nullptr);
	PGconn *handle;	
};

}

#endif
