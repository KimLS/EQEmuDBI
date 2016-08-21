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
#include "dbh-sqlite.h"
#include "sth-sqlite.h"
#include "rs.h"
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <cstddef>
#include <string>
#include "sqlite3.h"

DBI::SQLiteDatabaseHandle::SQLiteDatabaseHandle() : m_handle(nullptr) {
}

DBI::SQLiteDatabaseHandle::~SQLiteDatabaseHandle() {
	Disconnect();
}

void DBI::SQLiteDatabaseHandle::Connect(std::string dbname, std::string host, std::string username,
									   std::string auth, DatabaseAttributes &attr) {
	if(m_handle) {
		return;
	}

	int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
	std::string vfs;

	auto iter = attr.find("sqlite_vfs");
	if(iter != attr.end()) {
		vfs = iter->second;
	}

	iter = attr.find("sqlite_nomutex");
	if(iter != attr.end()) {
		int v = static_cast<int>(std::stoi(iter->second));
		if(v) {
			flags |= SQLITE_OPEN_NOMUTEX;
		}
	}

	iter = attr.find("sqlite_fullmutex");
	if(iter != attr.end()) {
		int v = static_cast<int>(std::stoi(iter->second));
		if(v) {
			flags |= SQLITE_OPEN_FULLMUTEX;
		}
	}

	iter = attr.find("sqlite_sharedcache");
	if(iter != attr.end()) {
		int v = static_cast<int>(std::stoi(iter->second));
		if(v) {
			flags |= SQLITE_OPEN_SHAREDCACHE;
		}
	}

	iter = attr.find("sqlite_privatecache");
	if(iter != attr.end()) {
		int v = static_cast<int>(std::stoi(iter->second));
		if(v) {
			flags |= SQLITE_OPEN_PRIVATECACHE;
		}
	}

	int rc = sqlite3_open_v2(dbname.c_str(), &m_handle, flags, vfs.empty() ? nullptr : vfs.c_str());

	if(rc) {
		auto error = std::string("Error failed to connect to database: ") + sqlite3_errmsg(m_handle);
		Disconnect();
		throw std::runtime_error(error);
	}
}

void DBI::SQLiteDatabaseHandle::Disconnect() {
	if(m_handle) {
		sqlite3_close(m_handle);
		m_handle = nullptr;
	}
}

std::unique_ptr<DBI::StatementHandle> DBI::SQLiteDatabaseHandle::Prepare(std::string stmt) {
	sqlite3_stmt *my_stmt = nullptr;
	int rc = sqlite3_prepare_v2(m_handle, stmt.c_str(), (int)stmt.length() + 1, &my_stmt, nullptr);
	if(rc != SQLITE_OK) {
		std::string err = "Prepare failure: ";
		err += sqlite3_errmsg(m_handle);

		if(my_stmt) {
			sqlite3_finalize(my_stmt);
		}

		throw std::runtime_error(err);
	}
	
	std::unique_ptr<DBI::StatementHandle> res(new SQLiteStatementHandle(m_handle, my_stmt));
	return res;
}

void DBI::SQLiteDatabaseHandle::Ping() {
}

void DBI::SQLiteDatabaseHandle::Begin() {
	Do("BEGIN");
}

void DBI::SQLiteDatabaseHandle::Commit() {
	Do("COMMIT");
}

void DBI::SQLiteDatabaseHandle::Rollback() {
	Do("ROLLBACK");
}

void DBI::SQLiteDatabaseHandle::BindArg(bool v, int i) {
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(int8_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(uint8_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(int16_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(uint16_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(int32_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(uint32_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(int64_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(uint64_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(float v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(double v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(const std::string &v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(const char *v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::SQLiteDatabaseHandle::BindArg(std::nullptr_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

std::unique_ptr<DBI::ResultSet> DBI::SQLiteDatabaseHandle::ExecuteDo()
{
	auto res = m_do_statement->InternalExecute();
	m_do_statement.release();
	return res;
}

void DBI::SQLiteDatabaseHandle::InitDo(const std::string& stmt)
{
	if (!m_do_statement) {
		sqlite3_stmt *my_stmt = nullptr;
		int rc = sqlite3_prepare_v2(m_handle, stmt.c_str(), (int)stmt.length() + 1, &my_stmt, nullptr);
		if (rc != SQLITE_OK) {
			if (my_stmt) {
				sqlite3_finalize(my_stmt);
			}

			std::string err = "Do failure: ";
			err += sqlite3_errmsg(m_handle);
			throw std::runtime_error(err);
		}

		m_do_statement.reset(new SQLiteStatementHandle(m_handle, my_stmt));
	}
}