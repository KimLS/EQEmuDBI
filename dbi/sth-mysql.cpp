#include "sth-mysql.h"

#ifndef SOCKET
#define SOCKET int
#endif
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>
#undef SOCKET

DBI::MySQLStatementHandle::MySQLStatementHandle(MYSQL *handle_, MYSQL_STMT *stmt_)
{
	m_handle = handle_;
	m_stmt = stmt_;
}

DBI::MySQLStatementHandle::~MySQLStatementHandle() {
	if (m_stmt) {
		mysql_stmt_close(m_stmt);
	}

	ClearBindParams();
}

void DBI::MySQLStatementHandle::BindArg(bool v, int i)
{
	int8_t t = 0;
	if (v) {
		t = 1;
	}

	BindArg(t, i);
}

void DBI::MySQLStatementHandle::BindArg(int8_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_TINY;
	auto p = new int8_t(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(uint8_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_TINY;
	auto p = new uint8_t(v);
	bind.buffer = p;
	bind.is_unsigned = 1;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(int16_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_SHORT;
	auto p = new int16_t(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(uint16_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_SHORT;
	auto p = new uint16_t(v);
	bind.buffer = p;
	bind.is_unsigned = 1;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(int32_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_LONG;
	auto p = new int32_t(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(uint32_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_LONG;
	auto p = new uint32_t(v);
	bind.buffer = p;
	bind.is_unsigned = 1;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(int64_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_LONGLONG;
	auto p = new int64_t(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(uint64_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_LONGLONG;
	auto p = new uint64_t(v);
	bind.buffer = p;
	bind.is_unsigned = 1;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(float v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_FLOAT;
	auto p = new float(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(double v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_DOUBLE;
	auto p = new double(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
}

void DBI::MySQLStatementHandle::BindArg(const std::string &v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_STRING;

	auto p = new char[v.length()];
	memcpy(p, v.c_str(), v.length());
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	bind.buffer_length = static_cast<unsigned long>(v.length());
}

void DBI::MySQLStatementHandle::BindArg(const char *v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_STRING;

	auto v_length = strlen(v);
	auto p = new char[v_length];
	memcpy(p, v, v_length);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	bind.buffer_length = static_cast<unsigned long>(v_length);
}

void DBI::MySQLStatementHandle::BindArg(std::nullptr_t v, int i)
{
	InitBindParam(i - 1);

	auto &bind = m_bind_params[i - 1];
	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_NULL;
	bind.buffer = nullptr;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
}

std::unique_ptr<DBI::ResultSet> DBI::MySQLStatementHandle::InternalExecute()
{
	if (m_bind_params.size() > 0) {
		if (mysql_stmt_bind_param(m_stmt, &m_bind_params[0])) {
			ClearBindParams();
			std::string err = "Statement execute failure: ";
			err += mysql_stmt_error(m_stmt);
			throw std::runtime_error(err);
		}
	}

	if (mysql_stmt_execute(m_stmt)) {
		ClearBindParams();
		std::string err = "Statement execute failure: ";
		err += mysql_stmt_error(m_stmt);
		throw std::runtime_error(err);
	}

	MYSQL_RES *res = mysql_stmt_result_metadata(m_stmt);
	std::vector<std::unique_ptr<char>> buffers;
	std::unique_ptr<MYSQL_BIND> results(nullptr);
	std::unique_ptr<my_bool> is_null(nullptr);
	std::unique_ptr<my_bool> err(nullptr);
	std::unique_ptr<unsigned long> len(nullptr);
	std::vector<std::string> field_names;
	uint32_t fields = 0;

	if (res) {
		fields = mysql_num_fields(res);
		if (fields != 0) {
			buffers.resize(fields);
			results.reset(new MYSQL_BIND[fields]);
			is_null.reset(new my_bool[fields]);
			err.reset(new my_bool[fields]);
			len.reset(new unsigned long[fields]);
			memset(results.get(), 0, sizeof(MYSQL_BIND) * fields);
			memset(is_null.get(), 0, sizeof(my_bool) * fields);
			memset(err.get(), 0, sizeof(my_bool) * fields);
			memset(len.get(), 0, sizeof(unsigned long) * fields);

			MYSQL_FIELD *f = nullptr;
			uint32_t i = 0;
			while ((f = mysql_fetch_field(res)) != nullptr) {
				field_names.push_back(std::string(f->name));

				buffers[i].reset(new char[f->length]);
				results.get()[i].buffer_type = MYSQL_TYPE_STRING;
				results.get()[i].buffer = buffers[i].get();
				results.get()[i].buffer_length = f->length;
				results.get()[i].is_null = &is_null.get()[i];
				results.get()[i].error = &err.get()[i];
				results.get()[i].length = &len.get()[i];
				++i;
			}

			mysql_stmt_bind_result(m_stmt, results.get());
		}
		mysql_free_result(res);
	}

	if (mysql_stmt_store_result(m_stmt)) {
		ClearBindParams();
		return nullptr;
	}

	std::list<DBI::ResultSet::Row> rows;
	while (!mysql_stmt_fetch(m_stmt)) {
		DBI::ResultSet::Row row;

		for (uint32_t i = 0; i < fields; ++i) {
			std::string val;
			if (len.get()[i] > 0) {
				val.assign(buffers[i].get(), len.get()[i]);
			}

			row[field_names[i]] = DBI::ResultSet::FieldData(is_null.get()[i] ? true : false, err.get()[i] ? true : false, val);
		}
		rows.push_back(row);
	}

	ClearBindParams();
	ResultSet *rs = new ResultSet(field_names, rows, static_cast<unsigned long>(mysql_stmt_affected_rows(m_stmt)));
	return std::unique_ptr<ResultSet>(rs);
}

void DBI::MySQLStatementHandle::ClearBindParams()
{
	for (auto &bind : m_bind_params) {
		if (bind.buffer_type == MYSQL_TYPE_STRING) {
			delete[] bind.buffer;
			continue;
		}

		if (bind.buffer_type == MYSQL_TYPE_NULL) {
			continue;
		}

		delete bind.buffer;
	}

	m_bind_params.clear();
}

void DBI::MySQLStatementHandle::InitBindParam(int i)
{
	if (i >= m_bind_params.size()) {
		m_bind_params.resize(i + 1);
	}
	else {
		auto &bind = m_bind_params[i];

		if (bind.buffer_type == MYSQL_TYPE_STRING) {
			delete[] bind.buffer;
		} else if (bind.buffer_type != MYSQL_TYPE_NULL) {
			delete bind.buffer;
		}
	}
}
