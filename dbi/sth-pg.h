#pragma once

#include "dbh-pg.h"
#include <vector>

struct pg_conn;
typedef struct pg_conn PGconn;

namespace DBI
{

	class ResultSet;

	class PGStatementHandle : public StatementHandle
	{
	public:
		virtual ~PGStatementHandle();

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

		PGStatementHandle(PGconn *conn_, std::string name_);

		PGconn *m_handle;
		std::string m_name;
		std::vector<char*> m_bind_params;

		friend class DBI::PGDatabaseHandle;
	};
}

