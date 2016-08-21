#pragma once

#include "dbh.h"

struct st_mysql;
typedef st_mysql MYSQL;

struct st_mysql_stmt;
typedef struct st_mysql_stmt MYSQL_STMT;

struct st_mysql_bind;
typedef struct st_mysql_bind MYSQL_BIND;

namespace DBI
{
	class MySQLStatementHandle;
	class MySQLDatabaseHandle : public DatabaseHandle
	{
	public:
		MySQLDatabaseHandle();
		virtual ~MySQLDatabaseHandle();

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

		MYSQL *m_handle;
		std::unique_ptr<MySQLStatementHandle> m_do_statement;
	};

}
