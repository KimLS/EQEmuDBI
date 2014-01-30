#include "dbh-pg.h"
#include "sth.h"
#include <stdint.h>
#include <assert.h>

DBI::PGDatabaseHandle::PGDatabaseHandle() {
	handle = nullptr;
}

DBI::PGDatabaseHandle::~PGDatabaseHandle() {
	Disconnect();
}

bool DBI::PGDatabaseHandle::Connect(std::string dbname, std::string host, std::string username,
									   std::string auth, DatabaseAttributes &attr) {
	if(handle) {
		return false;
	}
	
	std::string port;
	auto iter = attr.find("port");
	if(iter != attr.end()) {
		port = iter->second;
	}

	handle = PQsetdbLogin(host.c_str(), port.c_str(), nullptr, nullptr, dbname.c_str(), username.c_str(), auth.c_str());
	
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

bool DBI::PGDatabaseHandle::Do(std::string stmt) {
	StatementArguments args;
	return Do(stmt, args);
}

bool DBI::PGDatabaseHandle::Do(std::string stmt, DBI::StatementArguments &args) {
	assert(handle != nullptr);
	std::string query = _process_query(stmt);
	
	size_t nParams = args.size();
	char **paramValues = nullptr;

	if(nParams > 0) {
		paramValues = new char*[nParams];
		for(size_t i = 0; i < nParams; ++i) {
			paramValues[i] = nullptr;
		}

		for(size_t i = 0; i < nParams; ++i) {
			DBI::Any t = args[i];
			if(t.type() == typeid(bool)) {
				try {
					bool v = DBI::any_cast<bool>(t);
					paramValues[i] = new char[2];
					if(v) {
						paramValues[i][0] = '1';
					} else {
						paramValues[i][0] = '0';
					}
					paramValues[i][1] = '\0';
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from bool arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(uint8_t)) {
				try {
					uint8_t v = DBI::any_cast<uint8_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%u", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint8_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(int8_t)) {
				try {
					int8_t v = DBI::any_cast<int8_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%d", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int8_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(uint16_t)) {
				try {
					uint16_t v = DBI::any_cast<uint16_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%u", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint16_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(int16_t)) {
				try {
					int16_t v = DBI::any_cast<int16_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%d", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int16_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(uint32_t)) {
				try {
					uint32_t v = DBI::any_cast<uint32_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%u", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint32_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(int32_t)) {
				try {
					int32_t v = DBI::any_cast<int32_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%d", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int32_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(uint64_t)) {
				try {
					uint64_t v = DBI::any_cast<uint64_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%llu", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint64_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(int64_t)) {
				try {
					int64_t v = DBI::any_cast<int64_t>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%lld", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int64_t arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(float)) {
				try {
					float v = DBI::any_cast<float>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%f", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from float arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(double)) {
				try {
					double v = DBI::any_cast<double>(t);
					char val[64] = { 0 };
					size_t len = sprintf(val, "%f", v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], val, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from double arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(std::string)) {
				try {
					std::string v = DBI::any_cast<std::string>(t);
					size_t len = v.length();
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], v.c_str(), len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from std::string arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					for(size_t r = 0; r < nParams; ++r) {
						if(paramValues[r])
							delete[] paramValues[r];
					}
					delete[] paramValues;
					return false;
				}
			} else if(t.type() == typeid(const char*)) {
				try {
					const char *v = DBI::any_cast<const char*>(t);
					size_t len = strlen(v);
					paramValues[i] = new char[len + 1];
					strncpy(paramValues[i], v, len);
					paramValues[i][len] = 0;
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from const char* arg in DBI::PGDatabaseHandle::Do(stmt, args).");
					return false;
				}
			} else if(!t.empty() && t.type() != typeid(std::nullptr_t)) {
				SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from unknown arg in DBI::PGDatabaseHandle::Do(stmt, args).");
				for(size_t r = 0; r < nParams; ++r) {
					if(paramValues[r])
						delete[] paramValues[r];
				}
				delete[] paramValues;
				return false;
			}
		}
	}

	PGresult *res = PQexecParams(handle, query.c_str(), (int)nParams, nullptr, paramValues, nullptr, nullptr, 0); 
	
	if(PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK) {
		PQclear(res);
		for(size_t r = 0; r < nParams; ++r) {
			if(paramValues[r])
				delete[] paramValues[r];
		}
		return true;
	}

	std::string err = "PG Error: ";
	char *err_str = PQresultErrorMessage(res);
	err += err_str;
	SetError(DBH_ERROR_QUERY, err);

	PQclear(res);
	for(size_t r = 0; r < nParams; ++r) {
		if(paramValues[r])
			delete[] paramValues[r];
	}
	delete[] paramValues;
	return false;
}

std::string DBI::PGDatabaseHandle::Quote(std::string v) {
	assert(handle != nullptr);
	std::string ret = "'";

	if(!v.empty()) {
		char *escaped = PQescapeLiteral(handle, v.c_str(), v.length());
		ret += escaped;
		PQfreemem(escaped);
	}
	
	ret.push_back('\'');
	return ret;
}

DBI::StatementHandle* DBI::PGDatabaseHandle::Prepare(std::string stmt) {
	assert(handle != nullptr);
	//MYSQL_STMT *my_stmt = mysql_stmt_init(handle);
	//if(mysql_stmt_prepare(my_stmt, stmt.c_str(), static_cast<unsigned long>(stmt.length()))) {
	//	if(mysql_stmt_errno(my_stmt) == ER_UNSUPPORTED_PS) {
	//		server_side_prepare = false;
	//	}
	//	
	//	SetError(DBH_ERROR_PREPARE_FAILURE, "Could not prepare statement in DBI::MySQLDatabaseHandle::Prepare(stmt).");
	//	mysql_stmt_close(my_stmt);
	//	return nullptr;
	//}
	//
	//MySQLStatementHandle *sth = new MySQLStatementHandle(my_stmt);
	//return sth;
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
	return Do("BEGIN");
}

bool DBI::PGDatabaseHandle::Commit() {
	assert(handle != nullptr);
	return Do("COMMIT");
}

bool DBI::PGDatabaseHandle::Rollback() {
	assert(handle != nullptr);
	return Do("ROLLBACK");
}

std::string DBI::PGDatabaseHandle::_process_query(std::string stmt) {
	std::string ret;
	size_t sz = stmt.size();
	size_t current = 1;
	bool escaped = false;

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
		} else if(c == '$') {
			ret.push_back('\\');
			ret.push_back(c);
		} else {
			ret.push_back(c);
		}
	}

	return ret;
}
