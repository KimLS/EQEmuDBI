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
//#ifndef DBI__DBH_PGL_H
//#define DBI__DBH_PGL_H
//
//#include "dbh.h"
//
//struct pg_result;
//typedef struct pg_result PGresult;
//
//struct pg_conn;
//typedef struct pg_conn PGconn;
//
//namespace DBI
//{
//
//class PGStatementHandle;
//
//class PGDatabaseHandle : public DatabaseHandle
//{
//public:
//	virtual ~PGDatabaseHandle();
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
//	PGDatabaseHandle();
//	std::string _process_query(std::string stmt, int *params = nullptr);
//	static std::unique_ptr<ResultSet> _internal_results_from_postgresql(PGresult* res);
//	PGconn *handle;
//	uint32_t statement_index;
//
//	friend class DBI::DatabaseInterface;
//	friend class DBI::PGStatementHandle;
//};
//
//}
//
//#endif
//