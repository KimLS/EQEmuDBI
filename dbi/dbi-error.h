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
#ifndef DBI__DBI_ERROR_H
#define DBI__DBI_ERROR_H

#include <string>

namespace DBI
{

enum DBIErrorCode
{
	DBI_ERROR_NONE = 0,
	DBI_ERROR_DRIVER_NOT_FOUND,
	DBI_ERROR_FAILED_TO_CONNECT,
	DBH_ERROR_INVALID_ARGS,
	DBH_ERROR_QUERY,
	DBH_ERROR_BIND_FAILURE,
	DBH_ERROR_STMT_FAILURE,
	DBH_ERROR_PREPARE_FAILURE,
	DBH_ERROR_PING_CONNECTION,
	DBH_ERROR_BEGIN_FAILURE,
	DBH_ERROR_COMMIT_FAILURE,
	DBH_ERROR_ROLLBACK_FAILURE,
	STH_ERROR_INVALID_ARGS,
	STH_ERROR_BIND_FAILURE,
	STH_ERROR_STMT_FAILURE
};

class ErrorHandler
{
public:
	ErrorHandler() { }
	virtual ~ErrorHandler() { }
	
	bool Error() const { return error_code != DBI_ERROR_NONE; };
	std::string ErrorMessage() const { return error_message; }
	const DBIErrorCode ErrorCode() const { return error_code; }
protected:
	void SetError(DBIErrorCode code, std::string msg);
	std::string error_message;
	DBIErrorCode error_code;
};

}

#endif
