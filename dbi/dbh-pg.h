#ifndef DBI__DBH_PGL_H
#define DBI__DBH_PGL_H

#include "dbh.h"
#include <libpq-fe.h>

namespace DBI
{

class PGDatabaseHandle : public DatabaseHandle
{
public:
	PGDatabaseHandle();
	virtual ~PGDatabaseHandle();
	
	virtual bool Connect(std::string dbname, std::string host, std::string username,
		std::string auth, DatabaseAttributes &attr);
	virtual bool Disconnect();
	
	virtual bool Do(std::string stmt);
	virtual bool Do(std::string stmt, StatementArguments &args);
	virtual StatementHandle* Prepare(std::string stmt);
	virtual std::string Quote(std::string stmt);

	virtual bool Ping();
	virtual bool Begin();
	virtual bool Commit();
	virtual bool Rollback();

private:
	PGconn *handle;	
};

}

#endif
