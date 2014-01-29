#include "dbi.h"
#include "dbh-mysql.h"

DBI::DatabaseInterface* DBI::DatabaseInterface::_instance = nullptr;

DBI::DatabaseInterface::DatabaseInterface()
	: error_code(DBI_ERROR_NONE) {
	error_message[0] = '\0';
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
}

DBI::DatabaseHandle* DBI::DatabaseInterface::Connect(std::string driver, std::string dbname, std::string host, 
													 std::string username, std::string auth, DatabaseAttributes &attr) 
{
#ifdef MYSQL_ENGINE
	if(driver.compare("mysql") == 0) {
		DBI::DatabaseHandle *dbh = new MySQLDatabaseHandle();
		if(dbh->Connect(dbname, host, username, auth, attr)) {
			return dbh;
		}
		
		SetError(DBI_ERROR_FAILED_TO_CONNECT, "Failed to connect to the selected MySQL Database.");
		delete dbh;
		return nullptr;
	}
#endif

#ifdef POSTGRESQL_ENGINE
	if(driver.compare("pg") == 0) {
		
	}
#endif

	SetError(DBI_ERROR_DRIVER_NOT_FOUND, "Could not find a suitable driver for DBI::Connect.");
	return nullptr;
}

void DBI::DatabaseInterface::SetError(DBI::DatabaseInterfaceErrorCode code, const char *msg) {
	error_code = code;

	size_t msg_len = strlen(msg);
	if(msg_len < MAX_DBI_ERROR_MSG_LEN) {
		strcpy(error_message, msg);
		error_message[msg_len] = '\0';
	} else {
		strncpy(error_message, msg, MAX_DBI_ERROR_MSG_LEN - 1);
		error_message[MAX_DBI_ERROR_MSG_LEN] = '\0';
	}
}
