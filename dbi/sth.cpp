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
#include "sth.h"
#include "rs.h"

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0) {
	StatementArguments args(1, DBI::Any());
	args[0] = arg0;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1) {
	StatementArguments args(2, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2) {
	StatementArguments args(3, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3) {
	StatementArguments args(4, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4) {
	StatementArguments args(5, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	args[4] = arg4;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5) {
	StatementArguments args(6, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	args[4] = arg4;
	args[5] = arg5;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6) {
	StatementArguments args(7, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	args[4] = arg4;
	args[5] = arg5;
	args[6] = arg6;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7) {
	StatementArguments args(8, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	args[4] = arg4;
	args[5] = arg5;
	args[6] = arg6;
	args[7] = arg7;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7, DBI::Any arg8) {
	StatementArguments args(9, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	args[4] = arg4;
	args[5] = arg5;
	args[6] = arg6;
	args[7] = arg7;
	args[8] = arg8;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::StatementHandle::Execute(DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7, DBI::Any arg8, DBI::Any arg9) {
	StatementArguments args(10, DBI::Any());
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	args[4] = arg4;
	args[5] = arg5;
	args[6] = arg6;
	args[7] = arg7;
	args[8] = arg8;
	args[9] = arg9;
	return Execute(args);
}
