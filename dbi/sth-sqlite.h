#pragma once

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

		SQLiteStatementHandle(sqlite3 *handle_, sqlite3_stmt *stmt_);

		sqlite3 *m_handle;
		sqlite3_stmt *m_stmt;

		friend class DBI::SQLiteDatabaseHandle;
	};

}

