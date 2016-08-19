///*
//	Copyright(C) 2014 EQEmu
//	
//	This program is free software; you can redistribute it and/or
//	modify it under the terms of the GNU General Public License
//	as published by the Free Software Foundation; either version 2
//	of the License, or (at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//	
//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//*/
//#ifndef DBI__DBH_MYSQL_H
//#define DBI__DBH_MYSQL_H
//
//#include "dbh.h"
//
//struct st_mysql_stmt;
//typedef struct st_mysql_stmt MYSQL_STMT;
//
//struct st_mysql;
//typedef st_mysql MYSQL;
//
//namespace DBI
//{
//
//class MySQLStatementHandle;
//
//class MySQLDatabaseHandle : public DatabaseHandle
//{
//public:
//	virtual ~MySQLDatabaseHandle();
//	
//	virtual bool Connect(std::string dbname, std::string host, std::string username,
//		std::string auth, DatabaseAttributes &attr);
//	virtual bool Disconnect();
//	
//	virtual std::unique_ptr<ResultSet> Do(std::string stmt);
//	virtual std::unique_ptr<ResultSet> Do(std::string stmt, StatementArguments &args);
//	virtual std::unique_ptr<StatementHandle> Prepare(std::string stmt);
//
//	virtual bool Ping();
//	virtual bool Begin();
//	virtual bool Commit();
//	virtual bool Rollback();
//
//private:
//	MySQLDatabaseHandle();
//	std::unique_ptr<ResultSet> _basic_execute_server_side(std::string stmt, StatementArguments &args);
//	static std::unique_ptr<ResultSet> _internal_results_from_mysql_stmt(MYSQL_STMT* statement);
//	MYSQL* handle;
//
//	friend class DBI::DatabaseInterface;
//	friend class DBI::MySQLStatementHandle;
//};
//
//}
//
//#endif
//