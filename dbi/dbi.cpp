/*
	Copyright(C) 2014 EQEmu
	
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "dbi.h"
#ifdef MYSQL_ENGINE
#ifdef _WIN32
#include <Windows.h>
#endif
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>
#include "dbh-mysql.h"
#endif

#ifdef POSTGRESQL_ENGINE
#include "dbh-pg.h"
#endif

#ifdef SQLITE_ENGINE
#include "dbh-sqlite.h"
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
		std::unique_ptr<DBI::DatabaseHandle> dbh(new SQLiteDatabaseHandle());
		if(dbh->Connect(dbname, host, username, auth, attr)) {
			return dbh;
		}
		
		SetError(DBI_ERROR_FAILED_TO_CONNECT, "Failed to connect to the selected SQLite Database.");
		return nullptr;
	}
#endif

	SetError(DBI_ERROR_DRIVER_NOT_FOUND, "Could not find a suitable driver for DBI::Connect.");
	return nullptr;
}
