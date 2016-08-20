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
#ifndef DBI__DBH_MYSQL_H
#define DBI__DBH_MYSQL_H

#include "dbh.h"

struct st_mysql;
typedef st_mysql MYSQL;

struct st_mysql_stmt;
typedef struct st_mysql_stmt MYSQL_STMT;

struct st_mysql_bind;
typedef struct st_mysql_bind MYSQL_BIND;

namespace DBI
{

	class MySQLDatabaseHandle : public DatabaseHandle
	{
	public:
		MySQLDatabaseHandle();
		virtual ~MySQLDatabaseHandle();

		virtual void Connect(std::string dbname, std::string host, std::string username,
			std::string auth, DatabaseAttributes &attr);
		virtual void Disconnect();

		virtual std::unique_ptr<StatementHandle> Prepare(std::string stmt);

		virtual void Ping();
		virtual void Begin();
		virtual void Commit();
		virtual void Rollback();

	protected:
		virtual void BindArg(int8_t v);
		virtual void BindArg(uint8_t v);
		virtual void BindArg(int16_t v);
		virtual void BindArg(uint16_t v);
		virtual void BindArg(int32_t v);
		virtual void BindArg(uint32_t v);
		virtual void BindArg(int64_t v);
		virtual void BindArg(uint64_t v);
		virtual void BindArg(float v);
		virtual void BindArg(double v);
		virtual void BindArg(const std::string &v);
		virtual void BindArg(const char *v);
		virtual void BindArg(std::nullptr_t v);
		virtual std::unique_ptr<ResultSet> ExecuteDo();
		virtual void InitDo(const std::string& stmt);
		void ClearBindParams();

		MYSQL *m_handle;
		MYSQL_STMT *m_do_stmt;
		std::vector<MYSQL_BIND> m_bind_params;
	};

}

#endif
