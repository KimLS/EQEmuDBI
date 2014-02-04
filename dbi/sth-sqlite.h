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
#ifndef DBI__STH_SQLITE_H
#define DBI__STH_SQLITE_H

#include "sth.h"
#include "dbh-sqlite.h"

struct sqlite3;
struct sqlite3_stmt;

namespace DBI
{

class ResultSet;

class SQLiteStatementHandle : public StatementHandle
{
public:
	virtual ~SQLiteStatementHandle();
	
	virtual std::unique_ptr<ResultSet> Execute();
	virtual std::unique_ptr<ResultSet> Execute(StatementArguments &args);
private:
	SQLiteStatementHandle(sqlite3 *handle_, sqlite3_stmt *stmt_);

	sqlite3 *handle;
	sqlite3_stmt *stmt;

	friend class DBI::SQLiteDatabaseHandle;
};

}

#endif
