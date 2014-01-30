#include "sth-mysql.h"
#include "rs.h"
#include <stdint.h>

DBI::MySQLStatementHandle::MySQLStatementHandle(MYSQL_STMT *stmt) : statement(stmt) {
}

DBI::MySQLStatementHandle::~MySQLStatementHandle() {
	if(statement)
		mysql_stmt_close(statement);
}

bool DBI::MySQLStatementHandle::Execute() {
	StatementArguments args;
	return Execute(args);
}

bool DBI::MySQLStatementHandle::Execute(StatementArguments &args) {
	MYSQL_BIND *params = nullptr;
	size_t argc = args.size();
	if(argc > 0) {
		params = new MYSQL_BIND[argc];
		memset(params, 0, sizeof(MYSQL_BIND) * argc);

		DBI::Any *t = nullptr;
		for(size_t i = 0; i < argc; ++i) {
			t = &args[i];
			if(t->empty()) {
				params[i].buffer_type = MYSQL_TYPE_NULL;
				params[i].buffer = nullptr;
				params[i].is_unsigned = 0;
				params[i].is_null = nullptr;
				params[i].length = 0;
			} else if(t->type() == typeid(bool)) {
				try {
					bool* v = DBI::any_cast<bool>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_TINY;
						params[i].buffer = v;
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from bool arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(uint8_t)) {
				try {
					uint8_t* v = DBI::any_cast<uint8_t>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_TINY;
						params[i].buffer = v;
						params[i].is_unsigned = 1;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from uint8_t arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(int8_t)) {
				try {
					int8_t* v = DBI::any_cast<int8_t>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_TINY;
						params[i].buffer = v;
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from int8_t arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(uint16_t)) {
				try {
					uint16_t* v = DBI::any_cast<uint16_t>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_SHORT;
						params[i].buffer = v;
						params[i].is_unsigned = 1;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from uint16_t arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(int16_t)) {
				try {
					int16_t* v = DBI::any_cast<int16_t>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_SHORT;
						params[i].buffer = v;
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from int16_t arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(uint32_t)) {
				try {
					uint32_t* v = DBI::any_cast<uint32_t>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_LONG;
						params[i].buffer = v;
						params[i].is_unsigned = 1;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from uint32_t arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(int32_t)) {
				try {
					int32_t* v = DBI::any_cast<int32_t>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_LONG;
						params[i].buffer = v;
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from int32_t arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(uint64_t)) {
				try {
					uint64_t* v = DBI::any_cast<uint64_t>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_LONGLONG;
						params[i].buffer = v;
						params[i].is_unsigned = 1;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from uint64_t arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(int64_t)) {
				try {
					int64_t* v = DBI::any_cast<int64_t>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_LONGLONG;
						params[i].buffer = v;
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from int64_t arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(float)) {
				try {
					float* v = DBI::any_cast<float>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_FLOAT;
						params[i].buffer = v;
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from float arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(double)) {
				try {
					double* v = DBI::any_cast<double>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_DOUBLE;
						params[i].buffer = v;
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from double arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(std::string)) {
				try {
					std::string* v = DBI::any_cast<std::string>(&*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_STRING;
						params[i].buffer = (void*)v->c_str();
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
						params[i].buffer_length = static_cast<unsigned long>(v->length());
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from std::string arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(const char*)) {
				try {
					const char* v = DBI::any_cast<const char*>(*t);
					if(v) {
						params[i].buffer_type = MYSQL_TYPE_STRING;
						params[i].buffer = (void*)v;
						params[i].is_unsigned = 0;
						params[i].is_null = nullptr;
						params[i].length = 0;
						params[i].buffer_length = static_cast<unsigned long>(strlen(v));
					}
				} catch(DBI::bad_any_cast) {
					SetError(STH_ERROR_INVALID_ARGS, "Could not convert from const char* arg in DBI::MySQLStatementHandle::Execute(args).");
					mysql_stmt_close(statement);
					delete[] params;
					return false;
				}
			} else if(t->type() == typeid(nullptr_t)) {
				params[i].buffer_type = MYSQL_TYPE_NULL;
				params[i].buffer = nullptr;
				params[i].is_unsigned = 0;
				params[i].is_null = nullptr;
				params[i].length = 0;
			} else {
				SetError(STH_ERROR_INVALID_ARGS, "Could not convert from unknown arg in DBI::MySQLStatementHandle::Execute(args).");
				mysql_stmt_close(statement);
				delete[] params;
				return false;
			}
		}
		
		if(mysql_stmt_bind_param(statement, params)) {
			SetError(STH_ERROR_BIND_FAILURE, "Could not bind params in DBI::MySQLStatementHandle::Execute(args).");
			mysql_stmt_close(statement);
			delete[] params;
			return false;
		}

		if(mysql_stmt_execute(statement)) {
			SetError(STH_ERROR_STMT_FAILURE, "Could not execute statement in DBI::MySQLStatementHandle::Execute(args).");
			mysql_stmt_close(statement);
			delete[] params;
			return false;
		}
	} else {
		if(mysql_stmt_execute(statement)) {
			SetError(STH_ERROR_STMT_FAILURE, "Could not execute statement in DBI::MySQLStatementHandle::Execute(args).");
			mysql_stmt_close(statement);
			return false;
		}		
	}

	return true;
}

DBI::ResultSet* DBI::MySQLStatementHandle::Results() {
	MYSQL_RES *res = mysql_stmt_result_metadata(statement);
	if(res) {
		char **buffers = nullptr;
		MYSQL_BIND *results = nullptr;
		my_bool *is_null = nullptr;
		my_bool *err = nullptr;
		unsigned long *len = nullptr;
		std::vector<std::string> field_names;

		uint32_t fields = mysql_num_fields(res);
		if(fields == 0) {
			mysql_free_result(res);
			return nullptr;
		}

		buffers = new char*[fields];
		results = new MYSQL_BIND[fields];
		is_null = new my_bool[fields];
		err = new my_bool[fields];
		len = new unsigned long[fields];
		memset(buffers, 0, sizeof(char*) * fields);
		memset(results, 0, sizeof(MYSQL_BIND) * fields);
		memset(is_null, 0, sizeof(my_bool) * fields);
		memset(err, 0, sizeof(my_bool) * fields);
		memset(len, 0, sizeof(unsigned long) * fields);

		MYSQL_FIELD *f = nullptr;
		uint32_t i = 0;
		while(f = mysql_fetch_field(res)) {
			field_names.push_back(std::string(f->name));
			
			buffers[i] = new char[f->length];
			results[i].buffer_type = MYSQL_TYPE_STRING;
			results[i].buffer = buffers[i];
			results[i].buffer_length = f->length;
			results[i].is_null = &is_null[i];
			results[i].error = &err[i];
			results[i].length = &len[i];
			++i;
		}

		mysql_stmt_bind_result(statement, results);

		if(mysql_stmt_store_result(statement)) {
			for(uint32_t r = 0; r < fields; ++r) {
				delete[] buffers[r];
			}
			delete[] buffers;
			delete[] results;
			delete[] is_null;
			delete[] err;
			delete[] len;
			return nullptr;
		}

		std::list<DBI::ResultSet::Row> rows;
		while(!mysql_stmt_fetch(statement)) {
			DBI::ResultSet::Row row;

			for(uint32_t i = 0; i < fields; ++i) {
				std::string val;
				if(len[i] > 0) {
					val.assign(buffers[i], len[i]);
				}

				row[field_names[i]] = DBI::ResultSet::FieldData(is_null[i] ? true : false, err[i] ? true : false, val);
			}
			rows.push_back(row);
		}

		ResultSet *rs = new ResultSet(field_names, rows,
			static_cast<unsigned long>(mysql_stmt_affected_rows(statement)),
			static_cast<unsigned long>(mysql_stmt_num_rows(statement)),
			static_cast<unsigned long>(mysql_stmt_insert_id(statement)));

		for(uint32_t r = 0; r < fields; ++r) {
			delete[] buffers[r];
		}
		delete[] buffers;
		delete[] results;
		delete[] is_null;
		delete[] err;
		delete[] len;
		mysql_free_result(res);
		return rs;
	}
	return nullptr;
}
