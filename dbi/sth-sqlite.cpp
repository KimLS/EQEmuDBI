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
#include "sth-sqlite.h"
#include "rs.h"
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <memory>
#include "sqlite3.h"

DBI::SQLiteStatementHandle::SQLiteStatementHandle(sqlite3 *handle_, sqlite3_stmt *stmt_) : m_handle(handle_), m_stmt(stmt_) {
}

DBI::SQLiteStatementHandle::~SQLiteStatementHandle() {
	if(m_stmt) {
		sqlite3_finalize(m_stmt);
	}
}

void DBI::SQLiteStatementHandle::BindArg(int8_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_int(m_stmt, i, (int)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(uint8_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_int(m_stmt, i, (int)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(int16_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_int(m_stmt, i, (int)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(uint16_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_int(m_stmt, i, (int)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(int32_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_int(m_stmt, i, (int)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(uint32_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_int(m_stmt, i, (int)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(int64_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_int64(m_stmt, i, (int64_t)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(uint64_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_int64(m_stmt, i, (int64_t)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(float v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_double(m_stmt, i, (double)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(double v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_double(m_stmt, i, (double)v) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(const std::string &v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_text(m_stmt, i, v.c_str(), (int)v.length(), SQLITE_TRANSIENT) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(const char *v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_text(m_stmt, i, v, (int)strlen(v), SQLITE_TRANSIENT) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

void DBI::SQLiteStatementHandle::BindArg(std::nullptr_t v, int i)
{
	if (m_stmt == nullptr) {
		return;
	}

	if (sqlite3_bind_null(m_stmt, i) != SQLITE_OK) {
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
		std::string err = "Bind failure: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}
}

std::unique_ptr<DBI::ResultSet> DBI::SQLiteStatementHandle::InternalExecute()
{
	if (!m_stmt) {
		return nullptr;
	}

	int rc = 0;
	std::vector<std::string> field_names;
	std::list<DBI::ResultSet::Row> rows;
	bool field_names_found = false;
	int fields = 0;

	while ((rc = sqlite3_step(m_stmt)) == SQLITE_ROW) {
		if (!field_names_found) {
			fields = sqlite3_column_count(m_stmt);
			for (int f = 0; f < fields; ++f) {
				field_names.push_back(sqlite3_column_name(m_stmt, f));
			}
			field_names_found = true;
		}

		DBI::ResultSet::Row row;
		for (int f = 0; f < fields; ++f) {
			DBI::ResultSet::FieldData fd;
			fd.error = false;

			const unsigned char *v = sqlite3_column_text(m_stmt, f);
			int len = sqlite3_column_bytes(m_stmt, f);
			if (v) {
				fd.is_null = false;
				fd.value.assign((const char*)v, len);
			}
			else {
				fd.is_null = true;
			}
			row[field_names[f]] = fd;
		}
		rows.push_back(row);
	}

	if (rc != SQLITE_DONE) {
		sqlite3_reset(m_stmt);
		sqlite3_clear_bindings(m_stmt);

		std::string err = "Error executing prepared statement: ";
		err += sqlite3_errmsg(m_handle);
		throw std::runtime_error(err);
	}

	size_t affected_rows = (size_t)sqlite3_changes(m_handle);
	std::unique_ptr<DBI::ResultSet> rs(new DBI::ResultSet(field_names, rows, affected_rows));
	sqlite3_reset(m_stmt);
	sqlite3_clear_bindings(m_stmt);
	return rs;
}