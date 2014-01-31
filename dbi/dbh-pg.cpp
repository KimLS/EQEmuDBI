#include "dbh-pg.h"
#include "sth.h"
#include "rs.h"
#include <stdint.h>
#include <assert.h>
#include <memory>

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

DBI::ResultSet* DBI::PGDatabaseHandle::Do(std::string stmt) {
	StatementArguments args;
	return Do(stmt, args);
}

DBI::ResultSet* DBI::PGDatabaseHandle::Do(std::string stmt, DBI::StatementArguments &args) {
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
					
					std::shared_ptr<char> t(new char[len + 1]);
					paramValues.get()[i] = t.get();
					strncpy(t.get(), v.c_str(), len);
					t.get()[len] = 0;
					paramSave.push_back(t);
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
	
	if(PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK) {
		PQclear(res);

		//pg doesn't have a working result set yet, will change sometime in the next day but still todo incase it takes me longer:
		ResultSet *rs = new ResultSet();
		return rs;
	}

	std::string err = "PG Error: ";
	char *err_str = PQresultErrorMessage(res);
	err += err_str;
	SetError(DBH_ERROR_QUERY, err);

	PQclear(res);
	return nullptr;
}

DBI::StatementHandle* DBI::PGDatabaseHandle::Prepare(std::string stmt) {
	assert(handle != nullptr);
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
	ResultSet* rs = Do("BEGIN");
	if(rs) {
		delete rs;
		return true;
	}
	else
		return false;
}

bool DBI::PGDatabaseHandle::Commit() {
	assert(handle != nullptr);
	ResultSet* rs = Do("COMMIT");
	if(rs) {
		delete rs;
		return true;
	}
	else
		return false;
}

bool DBI::PGDatabaseHandle::Rollback() {
	assert(handle != nullptr);
	ResultSet* rs = Do("ROLLBACK");
	if(rs) {
		delete rs;
		return true;
	}
	else
		return false;
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
