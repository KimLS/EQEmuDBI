#include "dbi.h"
#ifdef MYSQL_ENGINE
#include "dbh-mysql.h"
#endif

#ifdef POSTGRESQL_ENGINE
#include "dbh-pg.h"
#endif

#ifdef SQLITE_ENGINE
//#include "dbh-sqlite.h"
#endif

DBI::DatabaseInterface* DBI::DatabaseInterface::_instance = nullptr;

DBI::DatabaseInterface::DatabaseInterface() {
}

DBI::DatabaseInterface::~DatabaseInterface() {
}

DBI::DatabaseInterface* DBI::DatabaseInterface::Instance() {
	if(_instance == nullptr) {
		_instance = new DBI::DatabaseInterface();
	}

	return _instance;
}

void DBI::DatabaseInterface::Drivers(std::list<std::string> &drivers) {
	drivers.clear();
#ifdef MYSQL_ENGINE
	drivers.push_back("mysql");
#endif
#ifdef POSTGRESQL_ENGINE
	drivers.push_back("postgresql");
#endif
#ifdef SQLITE_ENGINE
	drivers.push_back("sqlite");
#endif
}

std::unique_ptr<DBI::DatabaseHandle> DBI::DatabaseInterface::Connect(std::string driver, std::string dbname, std::string host, 
													 std::string username, std::string auth, DatabaseAttributes &attr) 
{
#ifdef MYSQL_ENGINE
	if(driver.compare("mysql") == 0) {
		std::unique_ptr<DBI::DatabaseHandle> dbh(new MySQLDatabaseHandle());
		if(dbh->Connect(dbname, host, username, auth, attr)) {
			return dbh;
		}
		
		SetError(DBI_ERROR_FAILED_TO_CONNECT, "Failed to connect to the selected MySQL Database.");
		return nullptr;
	}
#endif

#ifdef POSTGRESQL_ENGINE
	if(driver.compare("postgresql") == 0) {
		std::unique_ptr<DBI::DatabaseHandle> dbh(new PGDatabaseHandle());
		if(dbh->Connect(dbname, host, username, auth, attr)) {
			return dbh;
		}
		
		SetError(DBI_ERROR_FAILED_TO_CONNECT, "Failed to connect to the selected PostgreSQL Database.");
		return nullptr;
	}
#endif

#ifdef SQLITE_ENGINE
	if(driver.compare("sqlite") == 0) {
		//DBI::DatabaseHandle *dbh = new SQLiteDatabaseHandle();
		//if(dbh->Connect(dbname, host, username, auth, attr)) {
		//	return dbh;
		//}
		//
		//SetError(DBI_ERROR_FAILED_TO_CONNECT, "Failed to connect to the selected MySQL Database.");
		//delete dbh;
		return nullptr;
	}
#endif

	SetError(DBI_ERROR_DRIVER_NOT_FOUND, "Could not find a suitable driver for DBI::Connect.");
	return nullptr;
}
