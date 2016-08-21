#pragma once

#include "dbh.h"

struct sqlite3;

namespace DBI
{
	class SQLiteStatementHandle;
	class SQLiteDatabaseHandle : public DatabaseHandle
	{
	public:
		SQLiteDatabaseHandle();
		virtual ~SQLiteDatabaseHandle();
	
		virtual void Connect(std::string dbname, std::string host, std::string username,
			std::string auth, DatabaseAttributes &attr);
		virtual void Disconnect();
	
		virtual std::unique_ptr<StatementHandle> Prepare(std::string stmt);

		virtual void Ping();
		virtual void Begin();
		virtual void Commit();
		virtual void Rollback();

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
		virtual std::unique_ptr<ResultSet> ExecuteDo();
		virtual void InitDo(const std::string& stmt);

		sqlite3 *m_handle;
		std::unique_ptr<SQLiteStatementHandle> m_do_statement;
	};
}

