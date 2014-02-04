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
#include <assert.h>
#include "sqlite3.h"

DBI::SQLiteDatabaseHandle::SQLiteDatabaseHandle() : handle(nullptr) {
}

DBI::SQLiteDatabaseHandle::~SQLiteDatabaseHandle() {
	Disconnect();
}

bool DBI::SQLiteDatabaseHandle::Connect(std::string dbname, std::string host, std::string username,
									   std::string auth, DatabaseAttributes &attr) {
	if(handle) {
		return false;
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

	int rc = sqlite3_open_v2(dbname.c_str(), &handle, flags, vfs.empty() ? nullptr : vfs.c_str());

	if(rc) {
		SetError(DBI_ERROR_FAILED_TO_CONNECT, sqlite3_errmsg(handle));
		Disconnect();
		return false;
	}

	return true;
}

bool DBI::SQLiteDatabaseHandle::Disconnect() {
	if(handle) {
		sqlite3_close(handle);
		handle = nullptr;
		return true;
	}

	return false;
}

std::unique_ptr<DBI::ResultSet> DBI::SQLiteDatabaseHandle::Do(std::string stmt) {
	StatementArguments args;
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::SQLiteDatabaseHandle::Do(std::string stmt, DBI::StatementArguments &args) {
	sqlite3_stmt *my_stmt = nullptr;
	int rc = sqlite3_prepare_v2(handle, stmt.c_str(), (int)stmt.length() + 1, &my_stmt, nullptr);
	if(rc != SQLITE_OK) {
		std::string err = sqlite3_errmsg(handle);
		SetError(DBH_ERROR_PREPARE_FAILURE, err);
		if(my_stmt) {
			sqlite3_finalize(my_stmt);
		}
		return false;
	}

	int idx = 1;
	size_t nParams = args.size();
	if(nParams > 0) {
		for(size_t i = 0; i < nParams; ++i, ++idx) {
			DBI::Any t = args[i];
			if(t.type() == typeid(bool)) {
				try {
					bool v = DBI::any_cast<bool>(t);

					if(v) {
						if(sqlite3_bind_int(my_stmt, idx, 1) != SQLITE_OK) {
							sqlite3_finalize(my_stmt);
							SetError(DBH_ERROR_INVALID_ARGS, "Could not bind bool arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
							return nullptr;
						}
					} else {
						if(sqlite3_bind_int(my_stmt, idx, 0) != SQLITE_OK) {
							sqlite3_finalize(my_stmt);
							SetError(DBH_ERROR_INVALID_ARGS, "Could not bind bool arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
							return nullptr;
						}
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from bool arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(uint8_t)) {
				try {
					uint8_t v = DBI::any_cast<uint8_t>(t);
					if(sqlite3_bind_int(my_stmt, idx, (int)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind uint8_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint8_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(int8_t)) {
				try {
					int8_t v = DBI::any_cast<int8_t>(t);
					if(sqlite3_bind_int(my_stmt, idx, (int)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind int8_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int8_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(uint16_t)) {
				try {
					uint16_t v = DBI::any_cast<uint16_t>(t);
					if(sqlite3_bind_int(my_stmt, idx, (int)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind uint16_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint16_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(int16_t)) {
				try {
					int16_t v = DBI::any_cast<int16_t>(t);
					if(sqlite3_bind_int(my_stmt, idx, (int)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind int16_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int16_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(uint32_t)) {
				try {
					uint32_t v = DBI::any_cast<uint32_t>(t);
					if(sqlite3_bind_int(my_stmt, idx, (int)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind uint32_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint32_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(int32_t)) {
				try {
					int32_t v = DBI::any_cast<int32_t>(t);
					if(sqlite3_bind_int(my_stmt, idx, (int)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind int32_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int32_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(uint64_t)) {
				try {
					uint64_t v = DBI::any_cast<uint64_t>(t);
					if(sqlite3_bind_int64(my_stmt, idx, (sqlite3_int64)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind uint64_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint64_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(int64_t)) {
				try {
					int64_t v = DBI::any_cast<int64_t>(t);
					if(sqlite3_bind_int64(my_stmt, idx, (sqlite3_int64)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind int64_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int64_t arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(float)) {
				try {
					float v = DBI::any_cast<float>(t);
					if(sqlite3_bind_double(my_stmt, idx, (double)v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind float arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from float arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(double)) {
				try {
					double v = DBI::any_cast<double>(t);
					if(sqlite3_bind_double(my_stmt, idx, v) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind double arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from double arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(std::string)) {
				try {
					std::string v = DBI::any_cast<std::string>(t);
					if(sqlite3_bind_text(my_stmt, idx, v.c_str(), (int)v.length(), SQLITE_TRANSIENT) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind std::string arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from std::string arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(t.type() == typeid(const char*)) {
				try {
					const char *v = DBI::any_cast<const char*>(t);
					size_t len = strlen(v);
					
					if(sqlite3_bind_text(my_stmt, idx, v, (int)len, SQLITE_TRANSIENT) != SQLITE_OK) {
						sqlite3_finalize(my_stmt);
						SetError(DBH_ERROR_INVALID_ARGS, "Could not bind const char* arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from const char* arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					sqlite3_finalize(my_stmt);
					return nullptr;
				}
			} else if(!t.empty() && t.type() != typeid(std::nullptr_t)) {
				SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from unknown arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
				sqlite3_finalize(my_stmt);
				return nullptr;
			} else {
				if(sqlite3_bind_null(my_stmt, idx) != SQLITE_OK) {
					sqlite3_finalize(my_stmt);
					SetError(DBH_ERROR_INVALID_ARGS, "Could not bind null arg in DBI::SQLiteDatabaseHandle::Do(stmt, args).");
					return nullptr;
				}
			}
		}
	}

	rc = 0;
	std::vector<std::string> field_names;
	std::list<DBI::ResultSet::Row> rows;
	bool field_names_found = false;
	int fields = 0;
	while(rc = sqlite3_step(my_stmt) == SQLITE_ROW) {
		if(!field_names_found) {
			fields = sqlite3_column_count(my_stmt);
			for(int f = 0; f < fields; ++f) {
				field_names.push_back(sqlite3_column_name(my_stmt, f));
			}
			field_names_found = true;
		}
	
		DBI::ResultSet::Row row;
		for(int f = 0; f < fields; ++f) {
			DBI::ResultSet::FieldData fd;
			fd.error = false;
	
			const unsigned char *v = sqlite3_column_text(my_stmt, f);
			int len = sqlite3_column_bytes(my_stmt, f);
			if(v) {
				fd.is_null = false;
				fd.value.assign((const char*)v, len);
			} else {
				fd.is_null = true;
			}
			row[field_names[f]] = fd;
		}
		rows.push_back(row);
	}
	
	size_t affected_rows = (size_t)sqlite3_changes(handle);
	std::unique_ptr<DBI::ResultSet> rs(new DBI::ResultSet(field_names, rows, affected_rows));
	sqlite3_finalize(my_stmt);
	return rs;
}

std::unique_ptr<DBI::StatementHandle> DBI::SQLiteDatabaseHandle::Prepare(std::string stmt) {
	sqlite3_stmt *my_stmt = nullptr;
	int rc = sqlite3_prepare_v2(handle, stmt.c_str(), (int)stmt.length() + 1, &my_stmt, nullptr);
	if(rc != SQLITE_OK) {
		std::string err = sqlite3_errmsg(handle);
		SetError(DBH_ERROR_PREPARE_FAILURE, err);
		if(my_stmt) {
			sqlite3_finalize(my_stmt);
		}
		return nullptr;
	}
	
	std::unique_ptr<DBI::StatementHandle> res(new SQLiteStatementHandle(handle, my_stmt));
	return res;
}

bool DBI::SQLiteDatabaseHandle::Ping() {
	return true;
}

bool DBI::SQLiteDatabaseHandle::Begin() {
	auto rs = Do("BEGIN");
	if(rs) {
		return true;
	}
	return false;
}

bool DBI::SQLiteDatabaseHandle::Commit() {
	auto rs = Do("COMMIT");
	if(rs) {
		return true;
	}
	return false;
}

bool DBI::SQLiteDatabaseHandle::Rollback() {
	auto rs = Do("ROLLBACK");
	if(rs) {
		return true;
	}
	return false;
}
