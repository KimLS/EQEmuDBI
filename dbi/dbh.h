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
#ifndef DBI__DBH_H
#define DBI__DBH_H

#include "dbi.h"
#include "dbi-error.h"

namespace DBI
{

class StatementHandle;
class ResultSet;

class DatabaseHandle : public ErrorHandler
{
public:
	DatabaseHandle() { }
	virtual ~DatabaseHandle() { }
	
	virtual bool Connect(std::string dbname, std::string host, std::string username,
		std::string auth, DatabaseAttributes &attr) = 0;
	virtual bool Disconnect() = 0;
	
	virtual std::unique_ptr<ResultSet> Do(std::string stmt) = 0;
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, StatementArguments &args) = 0;
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8);
	virtual std::unique_ptr<ResultSet> Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
		DBI::Any arg6, DBI::Any arg7, DBI::Any arg8, DBI::Any arg9);

	virtual std::unique_ptr<StatementHandle> Prepare(std::string stmt) = 0;

	virtual bool Ping() = 0;
	virtual bool Begin() = 0;
	virtual bool Commit() = 0;
	virtual bool Rollback() = 0;
};

}

#endif
