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
#ifndef DBI__STH_MYSQL_H
#define DBI__STH_MYSQL_H

#include "dbh-mysql.h"

namespace DBI
{
	class ResultSet;

	class MySQLStatementHandle : public StatementHandle
	{
	public:
		virtual ~MySQLStatementHandle();

	protected:
		virtual void BindArg(bool v, int i);
		virtual void BindArg(int8_t v, int i);
		virtual void BindArg(uint8_t v, int i);
		virtual void BindArg(int16_t v, int i);
		virtual void BindArg(uint16_t v, int i);
		virtual void BindArg(int32_t v, int i);
		virtual void BindArg(uint32_t v, int i);
		virtual void BindArg(int64_t v, int i);
		virtual void BindArg(uint64_t v, int i);
		virtual void BindArg(float v, int i);
		virtual void BindArg(double v, int i);
		virtual void BindArg(const std::string &v, int i);
		virtual void BindArg(const char *v, int i);
		virtual void BindArg(std::nullptr_t v, int i);
		virtual std::unique_ptr<ResultSet> InternalExecute();
		void ClearBindParams();
		void InitBindParam(int i);

		MySQLStatementHandle(MYSQL *handle_, MYSQL_STMT *stmt_);

		MYSQL *m_handle;
		MYSQL_STMT *m_stmt;
		std::vector<MYSQL_BIND> m_bind_params;

		friend class DBI::MySQLDatabaseHandle;
	};

}

#endif
