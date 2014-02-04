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
#include "dbh.h"
#include "rs.h"

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0) {
	StatementArguments args;
	args.push_back(arg0);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7, DBI::Any arg8) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	args.push_back(arg8);
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7, DBI::Any arg8, DBI::Any arg9) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	args.push_back(arg8);
	args.push_back(arg9);
	return Do(stmt, args);
}
