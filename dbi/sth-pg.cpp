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
#include "sth-pg.h"
#include "rs.h"
#include <stdint.h>
#include <string.h>
#include <memory>
#include <libpq-fe.h>

#define BYTEAOID 17

DBI::PGStatementHandle::PGStatementHandle(PGconn *conn_, std::string name_) : m_handle(conn_), m_name(name_) {
}

DBI::PGStatementHandle::~PGStatementHandle() {

}

void DBI::PGStatementHandle::BindArg(bool v, int i)
{
	int8_t t = 0;
	if (v) {
		t = 1;
	}

	BindArg(t, i);
}

void DBI::PGStatementHandle::BindArg(int8_t v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%d", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(uint8_t v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%u", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(int16_t v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%d", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(uint16_t v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%u", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(int32_t v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%d", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(uint32_t v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%u", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(int64_t v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%lld", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(uint64_t v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%llu", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(float v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%f", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(double v, int i)
{
	InitBindParam(i - 1);

	char val[64] = { 0 };
	size_t len = sprintf(val, "%f", v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, val, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(const std::string &v, int i)
{
	InitBindParam(i - 1);

	if (v.length() != strlen(v.c_str())) {
		size_t dest_len = 0;
		auto converted = PQescapeByteaConn(m_handle, (unsigned char*)&v[0], v.length(), &dest_len);
		auto &bind = m_bind_params[i - 1];
		bind = new char[dest_len + 1];
		memcpy(bind, converted, dest_len);
		bind[dest_len] = 0;
		
		PQfreemem(converted);
	}
	else {
		auto &bind = m_bind_params[i - 1];
		bind = new char[v.length() + 1];
		memcpy(bind, v.c_str(), v.length());
		bind[v.length()] = 0;
	}
}

void DBI::PGStatementHandle::BindArg(const char *v, int i)
{
	InitBindParam(i - 1);
	auto len = strlen(v);

	auto &bind = m_bind_params[i - 1];
	bind = new char[len + 1];
	memcpy(bind, v, len);
	bind[len] = 0;
}

void DBI::PGStatementHandle::BindArg(std::nullptr_t v, int i)
{
	InitBindParam(i - 1);
}

std::unique_ptr<DBI::ResultSet> DBI::PGStatementHandle::InternalExecute()
{
	PGresult *res;
	if (m_bind_params.size() > 0) {
		res = PQexecPrepared(m_handle, m_name.c_str(), (int)m_bind_params.size(), &m_bind_params[0], nullptr, nullptr, 0);
	}
	else {
		res = PQexecPrepared(m_handle, m_name.c_str(), (int)m_bind_params.size(), nullptr, nullptr, nullptr, 0);
	}

	if (res) {
		if(PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK) {
			std::vector<std::string> field_names;
			std::list<DBI::ResultSet::Row> rows;
			int field_c = PQnfields(res);
			int row_c = PQntuples(res);
			for(int i = 0; i < field_c; ++i) {
				field_names.push_back(PQfname(res, i));
			}
		
			for(int r = 0; r < row_c; ++r) {
				DBI::ResultSet::Row row;
				for(int f = 0; f < field_c; ++f) {
					DBI::ResultSet::FieldData fd;
					fd.error = false;
					if(PQgetisnull(res, r, f)) {
						fd.is_null = true;
					} else {
						fd.is_null = false;
						Oid t = PQftype(res, f);
						if(t == BYTEAOID) {
							size_t len = 0;
							unsigned char *pure = PQunescapeBytea((const unsigned char*)PQgetvalue(res, r, f), &len);
							fd.value.assign((const char*)pure, len);
							PQfreemem(pure);
						} else {
							fd.value.assign(PQgetvalue(res, r, f), (size_t)PQgetlength(res, r, f));
						}
					}
		
					row[PQfname(res, f)] = fd;
				}
				rows.push_back(row);
			}
		
			size_t affected_rows = (size_t)atoi(PQcmdTuples(res));
			std::unique_ptr<DBI::ResultSet> rs(new DBI::ResultSet(field_names, rows, affected_rows));
		
			PQclear(res);
			return rs;
		}

		PQclear(res);
	}

	std::string error = "Internal Execute Error: ";
	error += PQerrorMessage(m_handle);
	throw std::runtime_error(error);
}

void DBI::PGStatementHandle::ClearBindParams()
{
	for (auto &param : m_bind_params) {
		delete[] param;
	}

	m_bind_params.clear();
}

void DBI::PGStatementHandle::InitBindParam(int i)
{
	if (i >= m_bind_params.size()) {
		m_bind_params.resize(i + 1);
	}
	else {
		auto &bind = m_bind_params[i];
		delete[] bind;
		bind = nullptr;
	}
}
