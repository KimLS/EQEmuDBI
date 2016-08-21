#pragma once

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

