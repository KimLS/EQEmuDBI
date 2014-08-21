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
#include "sth-mysql.h"
#include "rs-mysql.h"
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <memory>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>

DBI::MySQLStatementHandle::MySQLStatementHandle(MYSQL_STMT* stmt) {
	statement = stmt;
}

DBI::MySQLStatementHandle::~MySQLStatementHandle() {
	if(statement)
		mysql_stmt_close(statement);
}

std::unique_ptr<DBI::ResultSet> DBI::MySQLStatementHandle::Execute() {
	StatementArguments args;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::MySQLStatementHandle::Execute(StatementArguments &args) {
	assert(statement != nullptr);
	std::unique_ptr<MYSQL_BIND> params(nullptr);
	size_t argc = args.size();
	if(argc > 0) {
		params.reset(new MYSQL_BIND[argc]);
		memset(params.get(), 0, sizeof(MYSQL_BIND) * argc);

		DBI::Any *t = nullptr;
		for(size_t i = 0; i < argc; ++i) {
			t = &args[i];
			if(t->empty()) {
				params.get()[i].buffer_type = MYSQL_TYPE_NULL;
				params.get()[i].buffer = nullptr;
				params.get()[i].is_unsigned = 0;
				params.get()[i].is_null = nullptr;
				params.get()[i].length = 0;
			} else if(t->type() == typeid(bool)) {
				try {
					bool* v = DBI::any_cast<bool>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_TINY;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from bool arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(uint8_t)) {
				try {
					uint8_t* v = DBI::any_cast<uint8_t>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_TINY;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 1;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from uint8_t arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(int8_t)) {
				try {
					int8_t* v = DBI::any_cast<int8_t>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_TINY;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from int8_t arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(uint16_t)) {
				try {
					uint16_t* v = DBI::any_cast<uint16_t>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_SHORT;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 1;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from uint16_t arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(int16_t)) {
				try {
					int16_t* v = DBI::any_cast<int16_t>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_SHORT;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from int16_t arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(uint32_t)) {
				try {
					uint32_t* v = DBI::any_cast<uint32_t>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_LONG;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 1;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from uint32_t arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(int32_t)) {
				try {
					int32_t* v = DBI::any_cast<int32_t>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_LONG;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from int32_t arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(uint64_t)) {
				try {
					uint64_t* v = DBI::any_cast<uint64_t>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_LONGLONG;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 1;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from uint64_t arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(int64_t)) {
				try {
					int64_t* v = DBI::any_cast<int64_t>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_LONGLONG;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from int64_t arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(float)) {
				try {
					float* v = DBI::any_cast<float>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_FLOAT;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from float arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(double)) {
				try {
					double* v = DBI::any_cast<double>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_DOUBLE;
						params.get()[i].buffer = v;
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from double arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(std::string)) {
				try {
					std::string* v = DBI::any_cast<std::string>(&*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_STRING;
						params.get()[i].buffer = (void*)v->c_str();
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
						params.get()[i].buffer_length = static_cast<unsigned long>(v->length());
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from std::string arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(const char*)) {
				try {
					const char* v = DBI::any_cast<const char*>(*t);
					if(v) {
						params.get()[i].buffer_type = MYSQL_TYPE_STRING;
						params.get()[i].buffer = (void*)v;
						params.get()[i].is_unsigned = 0;
						params.get()[i].is_null = nullptr;
						params.get()[i].length = 0;
						params.get()[i].buffer_length = static_cast<unsigned long>(strlen(v));
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from const char* arg in DBI::MySQLStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t->type() == typeid(std::nullptr_t)) {
				params.get()[i].buffer_type = MYSQL_TYPE_NULL;
				params.get()[i].buffer = nullptr;
				params.get()[i].is_unsigned = 0;
				params.get()[i].is_null = nullptr;
				params.get()[i].length = 0;
			} else {
				SetError(STH_ERROR_INVALID_ARGS, "Could not convert from unknown arg in DBI::MySQLStatementHandle::Execute(args).");
				return nullptr;
			}
		}
		
		if(mysql_stmt_bind_param(statement, params.get())) {
			std::string err = mysql_stmt_error(statement);
			SetError(STH_ERROR_BIND_FAILURE, err);
			return nullptr;
		}

		if(mysql_stmt_execute(statement)) {
			std::string err = mysql_stmt_error(statement);
			SetError(STH_ERROR_STMT_FAILURE, err);
			return nullptr;
		}
	} else {
		if(mysql_stmt_execute(statement)) {
			std::string err = mysql_stmt_error(statement);
			SetError(STH_ERROR_STMT_FAILURE, err);
			return nullptr;
		}		
	}

	std::unique_ptr<ResultSet> res(DBI::MySQLDatabaseHandle::_internal_results_from_mysql_stmt(statement));
	return res;
}
