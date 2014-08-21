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
#include <assert.h>
#include <string.h>
#include <cstddef>
#include <libpq-fe.h>

#define BYTEAOID 17

DBI::PGDatabaseHandle::PGDatabaseHandle() {
	handle = nullptr;
	statement_index = 0;
}

DBI::PGDatabaseHandle::~PGDatabaseHandle() {
	Disconnect();
}

bool DBI::PGDatabaseHandle::Connect(std::string dbname, std::string host, std::string username,
									   std::string auth, DatabaseAttributes &attr) {
	if(handle) {
		return false;
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

	handle = PQconnectdb(connection_string.c_str());
	
	if(handle) {
		return true;
	}

	Disconnect();
	return false;
}

bool DBI::PGDatabaseHandle::Disconnect() {
	if(!handle)
		return false;

	PQfinish(handle);
	handle = nullptr;
	return true;
}

std::unique_ptr<DBI::ResultSet> DBI::PGDatabaseHandle::Do(std::string stmt) {
	StatementArguments args;
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::PGDatabaseHandle::Do(std::string stmt, DBI::StatementArguments &args) {
	assert(handle != nullptr);
	std::string query = _process_query(stmt);
	
	size_t nParams = args.size();
	std::list<std::shared_ptr<char>> paramSave;
	std::unique_ptr<char*> paramValues(nullptr);

	if(nParams > 0) {
		paramValues.reset(new char*[nParams]);
		for(size_t i = 0; i < nParams; ++i) {
			paramValues.get()[i] = nullptr;
		}

		for(size_t i = 0; i < nParams; ++i) {
			DBI::Any t = args[i];
			if(t.type() == typeid(bool)) {
				try {
					bool v = DBI::any_cast<bool>(t);

					std::shared_ptr<char> t(new char[2]);
					paramValues.get()[i] = t.get();
					if(v) {
						t.get()[0] = '1';
					} else {
						t.get()[0] = '0';
					}
					t.get()[1] = '\0';
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from bool arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(uint8_t)) {
				try {
					uint8_t v = DBI::any_cast<uint8_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%u", v);

					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint8_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(int8_t)) {
				try {
					int8_t v = DBI::any_cast<int8_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%d", v);

					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int8_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(uint16_t)) {
				try {
					uint16_t v = DBI::any_cast<uint16_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%u", v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint16_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(int16_t)) {
				try {
					int16_t v = DBI::any_cast<int16_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%d", v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int16_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(uint32_t)) {
				try {
					uint32_t v = DBI::any_cast<uint32_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%u", v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint32_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(int32_t)) {
				try {
					int32_t v = DBI::any_cast<int32_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%d", v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int32_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(uint64_t)) {
				try {
					uint64_t v = DBI::any_cast<uint64_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%llu", v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint64_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(int64_t)) {
				try {
					int64_t v = DBI::any_cast<int64_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%lld", v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int64_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(float)) {
				try {
					float v = DBI::any_cast<float>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%f", v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from float arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(double)) {
				try {
					double v = DBI::any_cast<double>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%f", v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), val, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from double arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(std::string)) {
				try {
					std::string v = DBI::any_cast<std::string>(t);
					size_t len = v.length();
					size_t clen = strlen(v.c_str());
					
					if(len != clen) {
						size_t conv_len = 0;
						unsigned char* converted = PQescapeByteaConn(handle, (const unsigned char*)v.c_str(), len, &conv_len);
						std::shared_ptr<char> t(new char[conv_len + 1]);
						paramValues.get()[i] = t.get();
						strncpy(t.get(), (const char*)converted, conv_len);
						t.get()[conv_len] = 0;
						paramSave.push_back(t);
						PQfreemem(converted);
					} else {
						std::shared_ptr<char> t(new char[len + 1]);
						paramValues.get()[i] = t.get();
						strncpy(t.get(), v.c_str(), len);
						t.get()[len] = 0;
						paramSave.push_back(t);
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from std::string arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(t.type() == typeid(const char*)) {
				try {
					const char *v = DBI::any_cast<const char*>(t);
					size_t len = strlen(v);
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), v, len);
					t.get()[len] = 0;
					paramSave.push_back(t);
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from const char* arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			} else if(!t.empty() && t.type() != typeid(std::nullptr_t)) {
				SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from unknown arg in DBI::PGDatabaseHandle::Do(stmt, args).");
				return nullptr;
			}
		}
	}

	PGresult *res = PQexecParams(handle, query.c_str(), (int)nParams, nullptr, paramValues.get(), nullptr, nullptr, 0); 
	
	std::unique_ptr<ResultSet> rs;
	if(res) {
		rs = DBI::PGDatabaseHandle::_internal_results_from_postgresql(res);
	}

	if(rs) {
		PQclear(res);
		return rs;
	}

	std::string err = PQresultErrorMessage(res);
	SetError(DBH_ERROR_QUERY, err);

	PQclear(res);
	return nullptr;
}

std::unique_ptr<DBI::StatementHandle> DBI::PGDatabaseHandle::Prepare(std::string stmt) {
	assert(handle != nullptr);
	int params = 0;
	std::string query = _process_query(stmt, &params);

	std::string name = "dbi_pg_";
	name += std::to_string((unsigned long)statement_index);
	statement_index++;

	PGresult * res = PQprepare(handle, name.c_str(), query.c_str(), params, nullptr); 
	if(PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK) {
		PQclear(res);
		
		std::unique_ptr<DBI::StatementHandle> st(new DBI::PGStatementHandle(handle, name));
		return st;
	}

	PQclear(res);
	return nullptr;
}

bool DBI::PGDatabaseHandle::Ping() {
	assert(handle != nullptr);
	
	if(PQstatus(handle) != CONNECTION_OK)
	{
		PQreset(handle);
		if(PQstatus(handle) != CONNECTION_OK)
		{
			return false;
		}
	}

	return true;
}

bool DBI::PGDatabaseHandle::Begin() {
	assert(handle != nullptr);
	std::unique_ptr<ResultSet> rs(Do("BEGIN"));
	if(rs) {
		return true;
	}
	else
		return false;
}

bool DBI::PGDatabaseHandle::Commit() {
	assert(handle != nullptr);
	std::unique_ptr<ResultSet> rs(Do("COMMIT"));
	if(rs) {
		return true;
	}
	else
		return false;
}

bool DBI::PGDatabaseHandle::Rollback() {
	assert(handle != nullptr);
	std::unique_ptr<ResultSet> rs(Do("ROLLBACK"));
	if(rs) {
		return true;
	}
	else
		return false;
}

std::string DBI::PGDatabaseHandle::_process_query(std::string stmt, int *params) {
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

std::unique_ptr<DBI::ResultSet> DBI::PGDatabaseHandle::_internal_results_from_postgresql(PGresult* res) {
	assert(res != nullptr);
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

		return rs;
	}
	return nullptr;
}
