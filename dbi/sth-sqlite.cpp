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

DBI::SQLiteStatementHandle::SQLiteStatementHandle(sqlite3 *handle_, sqlite3_stmt *stmt_) : handle(handle_), stmt(stmt_) {
}

DBI::SQLiteStatementHandle::~SQLiteStatementHandle() {
	if(stmt) {
		sqlite3_finalize(stmt);
	}
}

std::unique_ptr<DBI::ResultSet> DBI::SQLiteStatementHandle::Execute() {
	StatementArguments args;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::SQLiteStatementHandle::Execute(StatementArguments &args) {
	assert(stmt != nullptr);
	assert(handle != nullptr);
	int idx = 1;
	size_t nParams = args.size();
	if(nParams > 0) {
		for(size_t i = 0; i < nParams; ++i, ++idx) {
			DBI::Any t = args[i];
			if(t.type() == typeid(bool)) {
				try {
					bool v = DBI::any_cast<bool>(t);

					if(v) {
						if(sqlite3_bind_int(stmt, idx, 1) != SQLITE_OK) {
							SetError(STH_ERROR_STMT_FAILURE, "Could not bind bool arg in DBI::SQLiteStatementHandle::Execute( args).");
							return nullptr;
						}
					} else {
						if(sqlite3_bind_int(stmt, idx, 0) != SQLITE_OK) {
							SetError(STH_ERROR_STMT_FAILURE, "Could not bind bool arg in DBI::SQLiteStatementHandle::Execute( args).");
							return nullptr;
						}
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from bool arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(uint8_t)) {
				try {
					uint8_t v = DBI::any_cast<uint8_t>(t);
					if(sqlite3_bind_int(stmt, idx, (int)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind uint8_t arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from uint8_t arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(int8_t)) {
				try {
					int8_t v = DBI::any_cast<int8_t>(t);
					if(sqlite3_bind_int(stmt, idx, (int)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind int8_t arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from int8_t arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(uint16_t)) {
				try {
					uint16_t v = DBI::any_cast<uint16_t>(t);
					if(sqlite3_bind_int(stmt, idx, (int)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind uint16_t arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from uint16_t arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(int16_t)) {
				try {
					int16_t v = DBI::any_cast<int16_t>(t);
					if(sqlite3_bind_int(stmt, idx, (int)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind int16_t arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from int16_t arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(uint32_t)) {
				try {
					uint32_t v = DBI::any_cast<uint32_t>(t);
					if(sqlite3_bind_int(stmt, idx, (int)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind uint32_t arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from uint32_t arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(int32_t)) {
				try {
					int32_t v = DBI::any_cast<int32_t>(t);
					if(sqlite3_bind_int(stmt, idx, (int)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind int32_t arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from int32_t arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(uint64_t)) {
				try {
					uint64_t v = DBI::any_cast<uint64_t>(t);
					if(sqlite3_bind_int64(stmt, idx, (sqlite3_int64)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind uint64_t arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from uint64_t arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(int64_t)) {
				try {
					int64_t v = DBI::any_cast<int64_t>(t);
					if(sqlite3_bind_int64(stmt, idx, (sqlite3_int64)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind int64_t arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from int64_t arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(float)) {
				try {
					float v = DBI::any_cast<float>(t);
					if(sqlite3_bind_double(stmt, idx, (double)v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind float arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from float arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(double)) {
				try {
					double v = DBI::any_cast<double>(t);
					if(sqlite3_bind_double(stmt, idx, v) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind double arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from double arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(std::string)) {
				try {
					std::string v = DBI::any_cast<std::string>(t);
					size_t len = v.length();
					
					if(sqlite3_bind_text(stmt, idx, v.c_str(), (int)len, SQLITE_TRANSIENT) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind std::string arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from std::string arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(t.type() == typeid(const char*)) {
				try {
					const char *v = DBI::any_cast<const char*>(t);
					size_t len = strlen(v);
					
					if(sqlite3_bind_text(stmt, idx, v, (int)len, SQLITE_TRANSIENT) != SQLITE_OK) {
						SetError(STH_ERROR_STMT_FAILURE, "Could not bind const char* arg in DBI::SQLiteStatementHandle::Execute( args).");
						return nullptr;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not convert from const char* arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			} else if(!t.empty() && t.type() != typeid(std::nullptr_t)) {
				SetError(STH_ERROR_STMT_FAILURE, "Could not convert from unknown arg in DBI::SQLiteStatementHandle::Execute( args).");
				return nullptr;
			} else {
				if(sqlite3_bind_null(stmt, idx) != SQLITE_OK) {
					SetError(STH_ERROR_STMT_FAILURE, "Could not bind null arg in DBI::SQLiteStatementHandle::Execute( args).");
					return nullptr;
				}
			}
		}
	}

	int rc = 0;
	std::vector<std::string> field_names;
	std::list<DBI::ResultSet::Row> rows;
	bool field_names_found = false;
	int fields = 0;
	while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		if(!field_names_found) {
			fields = sqlite3_column_count(stmt);
			for(int f = 0; f < fields; ++f) {
				field_names.push_back(sqlite3_column_name(stmt, f));
			}
		}

		DBI::ResultSet::Row row;
		for(int f = 0; f < fields; ++f) {
			DBI::ResultSet::FieldData fd;
			fd.error = false;
			const unsigned char *v = sqlite3_column_text(stmt, f);
			int len = sqlite3_column_bytes(stmt, f);
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

	sqlite3_reset(stmt);
	size_t affected_rows = sqlite3_changes(handle);
	std::unique_ptr<DBI::ResultSet> rs(new DBI::ResultSet(field_names, rows, affected_rows));
	return rs;
}
