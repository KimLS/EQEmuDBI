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
#include "dbh-pg.h"
#include "sth-pg.h"
#include "rs.h"
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <cstddef>
#include <string>
#include <libpq-fe.h>

DBI::PGDatabaseHandle::PGDatabaseHandle() : m_handle(nullptr) {
}

DBI::PGDatabaseHandle::~PGDatabaseHandle() {
	Disconnect();
}

void DBI::PGDatabaseHandle::Connect(std::string dbname, std::string host, std::string username,
	std::string auth, DatabaseAttributes &attr)
{
	if(m_handle) {
		return;
	}
	
	std::string connection_string = "dbname = '";
	connection_string += dbname;
	connection_string += "' host ='";
	connection_string += host;
	connection_string += "' user ='";
	connection_string += username;
	connection_string += "' password ='";
	connection_string += auth; 
	connection_string += "'";
	
	auto iter = attr.find("pg_port");
	if(iter != attr.end()) {
		connection_string += " port ='";
		connection_string += iter->second; 
		connection_string += "'";
	}
	
	iter = attr.find("pg_connect_timeout");
	if(iter != attr.end()) {
		connection_string += " connect_timeout ='";
		connection_string += iter->second; 
		connection_string += "'";
	}
	
	iter = attr.find("pg_options");
	if(iter != attr.end()) {
		connection_string += " options ='";
		connection_string += iter->second; 
		connection_string += "'";
	}
	
	iter = attr.find("pg_sslmode");
	if(iter != attr.end()) {
		connection_string += " sslmode ='";
		connection_string += iter->second; 
		connection_string += "'";
	}
	
	iter = attr.find("pg_krbsrvname");
	if(iter != attr.end()) {
		connection_string += " krbsrvname ='";
		connection_string += iter->second; 
		connection_string += "'";
	}
	
	iter = attr.find("pg_gsslib");
	if(iter != attr.end()) {
		connection_string += " gsslib ='";
		connection_string += iter->second; 
		connection_string += "'";
	}
	
	iter = attr.find("pg_service");
	if(iter != attr.end()) {
		connection_string += " service ='";
		connection_string += iter->second; 
		connection_string += "'";
	}
	
	m_handle = PQconnectdb(connection_string.c_str());
		
	auto status = PQstatus(m_handle);
	if (status != CONNECTION_OK) {
		std::string error = "Failed to connect to database: ";
		error += PQerrorMessage(m_handle);
		Disconnect();
		throw std::runtime_error(error);
	}

}

void DBI::PGDatabaseHandle::Disconnect() {
	if (m_handle) {
		PQfinish(m_handle);
		m_handle = nullptr;
	}
}

std::unique_ptr<DBI::StatementHandle> DBI::PGDatabaseHandle::Prepare(std::string stmt) {
	int params = 0;
	std::string query = InternalProcessQuery(stmt, &params);
	
	PGresult *res = PQprepare(m_handle, "", query.c_str(), params, nullptr); 
	if(PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK) {
		PQclear(res);

		std::unique_ptr<DBI::StatementHandle> st(new DBI::PGStatementHandle(m_handle, ""));
		return st;
	}
	
	std::string error = "Prepare Error: ";
	error += PQresultErrorMessage(res);
	PQclear(res);
	throw std::runtime_error(error);
}

std::unique_ptr<DBI::StatementHandle> DBI::PGDatabaseHandle::Prepare(std::string stmt, std::string name)
{
	int params = 0;
	std::string query = InternalProcessQuery(stmt, &params);

	PGresult *res = PQprepare(m_handle, name.c_str(), query.c_str(), params, nullptr);
	if (PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK) {
		PQclear(res);

		std::unique_ptr<DBI::StatementHandle> st(new DBI::PGStatementHandle(m_handle, name));
		return st;
	}

	std::string error = "Prepare Error: ";
	error += PQresultErrorMessage(res);
	PQclear(res);
	throw std::runtime_error(error);
}

void DBI::PGDatabaseHandle::Ping() {
	auto status = PQstatus(m_handle);
	if (status != CONNECTION_OK)
	{
		PQreset(m_handle);
		status = PQstatus(m_handle);

		if(status != CONNECTION_OK) {
			throw std::runtime_error("Could not perform database ping, connection seems to be lost.");
		}
	}
}

void DBI::PGDatabaseHandle::Begin() {
	Do("BEGIN");
}

void DBI::PGDatabaseHandle::Commit() {
	Do("COMMIT");
}

void DBI::PGDatabaseHandle::Rollback() {
	Do("ROLLBACK");
}

void DBI::PGDatabaseHandle::BindArg(bool v, int i) {
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(int8_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(uint8_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(int16_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(uint16_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(int32_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(uint32_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(int64_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(uint64_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(float v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(double v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(const std::string &v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(const char *v, int i)
{
	m_do_statement->BindArg(v, i);
}

void DBI::PGDatabaseHandle::BindArg(std::nullptr_t v, int i)
{
	m_do_statement->BindArg(v, i);
}

std::unique_ptr<DBI::ResultSet> DBI::PGDatabaseHandle::ExecuteDo()
{
	auto res = m_do_statement->InternalExecute();
	m_do_statement.release();
	return res;
}

void DBI::PGDatabaseHandle::InitDo(const std::string& stmt)
{
	if (!m_do_statement) {
		int params = 0;
		std::string query = InternalProcessQuery(stmt, &params);

		PGresult *res = PQprepare(m_handle, "", query.c_str(), params, nullptr);
		if (PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK) {
			PQclear(res);

			m_do_statement.reset(new DBI::PGStatementHandle(m_handle, ""));
			return;
		}

		std::string error = "Prepare Error: ";
		error += PQresultErrorMessage(res);
		PQclear(res);
		throw std::runtime_error(error);
	}
}

std::string DBI::PGDatabaseHandle::InternalProcessQuery(std::string stmt, int *params) {
	std::string ret;
	size_t sz = stmt.size();
	size_t current = 1;
	bool escaped = false;

	if(params)
		*params = 0;

	for(size_t i = 0; i < sz; ++i) {
		char c = stmt[i];
		if(escaped) {
			ret.push_back(c);
			escaped = false;
		} else if(c == '\\') {
			ret.push_back(c);
			escaped = true;
		} else if(c == '?') {
			ret.push_back('$');
			ret += std::to_string((unsigned long)current++);
			if(params)
				*params = *params + 1;
		} else {
			ret.push_back(c);
		}
	}

	return ret;
}
