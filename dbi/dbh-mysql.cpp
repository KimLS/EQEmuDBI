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
#include "dbh-mysql.h"
#include "sth-mysql.h"
#include "rs-mysql.h"
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <cstddef>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>

DBI::MySQLDatabaseHandle::MySQLDatabaseHandle() {
	handle = nullptr;
}

DBI::MySQLDatabaseHandle::~MySQLDatabaseHandle() {
	Disconnect();
}

bool DBI::MySQLDatabaseHandle::Connect(std::string dbname, std::string host, std::string username,
									   std::string auth, DatabaseAttributes &attr) {
	if(handle) {
		return false;
	}
	
	handle = mysql_init(handle);
	if(!handle) {
		return false;
	}
	
	unsigned int client_flag = 0;
	auto iter = attr.find("mysql_init_command");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_INIT_COMMAND, iter->second.c_str());
	}
	
	iter = attr.find("mysql_compress");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_OPT_COMPRESS, nullptr);
	}
	
	iter = attr.find("mysql_connect_timeout");
	if(iter != attr.end()) {
		int t = std::stoi(iter->second);
		mysql_options(handle, MYSQL_OPT_CONNECT_TIMEOUT, &t);
	}
	
	iter = attr.find("mysql_local_infile");
	if(iter != attr.end()) {
		unsigned int t = static_cast<unsigned int>(std::stoi(iter->second));
		mysql_options(handle, MYSQL_OPT_LOCAL_INFILE, &t);
	}
	
	iter = attr.find("mysql_named_pipe");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_OPT_RECONNECT, nullptr);
	}
	
	iter = attr.find("mysql_protocol");
	if(iter != attr.end()) {
		unsigned int t = static_cast<unsigned int>(std::stoi(iter->second));
		mysql_options(handle, MYSQL_OPT_PROTOCOL, &t);
	}
	
	iter = attr.find("mysql_read_timeout");
	if(iter != attr.end()) {
		unsigned int t = static_cast<unsigned int>(std::stoi(iter->second));
		mysql_options(handle, MYSQL_OPT_READ_TIMEOUT, &t);
	}
	
	iter = attr.find("mysql_reconnect");
	if(iter != attr.end()) {
		my_bool t = static_cast<my_bool>(std::stoi(iter->second));
		mysql_options(handle, MYSQL_OPT_RECONNECT, &t);
	}
	
	iter = attr.find("mysql_ssl_verify_server_cert");
	if(iter != attr.end()) {
		my_bool t = static_cast<my_bool>(std::stoi(iter->second));
		mysql_options(handle, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &t);
	}
	
	iter = attr.find("mysql_use_result");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_OPT_USE_RESULT, nullptr);
	}
	
	iter = attr.find("mysql_write_timeout");
	if(iter != attr.end()) {
		unsigned int t = static_cast<unsigned int>(std::stoi(iter->second));
		mysql_options(handle, MYSQL_OPT_WRITE_TIMEOUT, &t);
	}
	
	iter = attr.find("mysql_read_default_file");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_READ_DEFAULT_FILE, iter->second.c_str());
	}
	
	iter = attr.find("mysql_read_default_group");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_READ_DEFAULT_GROUP, iter->second.c_str());
	}
	
	iter = attr.find("mysql_report_data_truncation");
	if(iter != attr.end()) {
		my_bool t = static_cast<my_bool>(std::stoi(iter->second));
		mysql_options(handle, MYSQL_REPORT_DATA_TRUNCATION, &t);
	}
	
	iter = attr.find("mysql_secure_auth");
	if(iter != attr.end()) {
		my_bool t = static_cast<my_bool>(std::stoi(iter->second));
		mysql_options(handle, MYSQL_SECURE_AUTH, &t);
	}
	
	iter = attr.find("mysql_charset_dir");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_SET_CHARSET_DIR, iter->second.c_str());
	}
	
	iter = attr.find("mysql_charset_name");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_SET_CHARSET_NAME, iter->second.c_str());
	}
	
	iter = attr.find("mysql_shared_memory_base_name");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_SHARED_MEMORY_BASE_NAME, iter->second.c_str());
	}
	
	iter = attr.find("mysql_read_default_group");
	if(iter != attr.end()) {
		mysql_options(handle, MYSQL_READ_DEFAULT_GROUP, iter->second.c_str());
	}
	
	iter = attr.find("mysql_ssl");
	if(iter != attr.end()) {
		char t = static_cast<char>(std::stoi(iter->second));
		if(t != 0) {
			std::string client_key;
			std::string client_cert;
			std::string ca_file;
			std::string ca_path;
			std::string cipher;
			char verify_true = 0;
	
			iter = attr.find("mysql_ssl_verify_server_cert");
			if(iter != attr.end()) {
				t = static_cast<char>(std::stoi(iter->second));
				verify_true = t != 0 ? true : false;
			}
	
			iter = attr.find("mysql_ssl_client_key");
			if(iter != attr.end()) {
				client_key = iter->second;
			}
	
			iter = attr.find("mysql_ssl_client_cert");
			if(iter != attr.end()) {
				client_cert = iter->second;
			}
	
			iter = attr.find("mysql_ssl_ca_file");
			if(iter != attr.end()) {
				ca_file = iter->second;
			}
	
			iter = attr.find("mysql_ssl_ca_path");
			if(iter != attr.end()) {
				ca_path = iter->second;
			}
	
			iter = attr.find("mysql_ssl_cipher");
			if(iter != attr.end()) {
				cipher = iter->second;
			}
	
			mysql_ssl_set(handle,
				client_key.empty() ? nullptr : client_key.c_str(),
				client_cert.empty() ? nullptr : client_cert.c_str(),
				ca_file.empty() ? nullptr : ca_file.c_str(),
				ca_path.empty() ? nullptr : ca_path.c_str(),
				cipher.empty() ? nullptr : cipher.c_str());
	
			mysql_options(handle, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &verify_true);
			client_flag |= CLIENT_SSL;
		}
	}
	
	std::string socket;
	int port = 0;
	iter = attr.find("mysql_unix_socket");
	if(iter != attr.end()) {
		socket = iter->second;
	}
	
	iter = attr.find("mysql_port");
	if(iter != attr.end()) {
		port = static_cast<int>(std::stoi(iter->second));
	}
	
	MYSQL* result = mysql_real_connect(handle, host.c_str(), username.c_str(), auth.c_str(), dbname.c_str(), port, 
		socket.empty() ? nullptr : socket.c_str(), client_flag);
	
	if(result) {
		return true;
	}
	

	Disconnect();
	return false;
}

bool DBI::MySQLDatabaseHandle::Disconnect() {
	if(!handle)
		return false;

	mysql_close(handle);
	handle = nullptr;
	return true;
}

std::unique_ptr<DBI::ResultSet> DBI::MySQLDatabaseHandle::Do(std::string stmt) {
	StatementArguments args;
	return Do(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::MySQLDatabaseHandle::Do(std::string stmt, DBI::StatementArguments &args) {
	return _basic_execute_server_side(stmt, args);
}

std::unique_ptr<DBI::ResultSet> DBI::MySQLDatabaseHandle::_basic_execute_server_side(std::string stmt, DBI::StatementArguments &args) {
	assert(handle != nullptr);
	MYSQL_STMT *my_stmt = mysql_stmt_init(handle);
	if(mysql_stmt_prepare(my_stmt, stmt.c_str(), static_cast<unsigned long>(stmt.length()))) {
		std::string err = mysql_stmt_error(my_stmt);
		SetError(DBH_ERROR_PREPARE_FAILURE, err);
		mysql_stmt_close(my_stmt);
		return nullptr;
	} else {
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from bool arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint8_t arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int8_t arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint16_t arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int16_t arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint32_t arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int32_t arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint64_t arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int64_t arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from float arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from double arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from std::string arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
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
						SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from const char* arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
						mysql_stmt_close(my_stmt);
						return nullptr;
					}
				} else if(t->type() == typeid(std::nullptr_t)) {
					params.get()[i].buffer_type = MYSQL_TYPE_NULL;
					params.get()[i].buffer = nullptr;
					params.get()[i].is_unsigned = 0;
					params.get()[i].is_null = nullptr;
					params.get()[i].length = 0;
				} else {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from unknown arg in DBI::MySQLDatabaseHandle::_basic_execute_server_side(stmt, args).");
					mysql_stmt_close(my_stmt);
					return nullptr;
				}
			}
			
			if(mysql_stmt_bind_param(my_stmt, params.get())) {
				std::string err = mysql_stmt_error(my_stmt);
				SetError(DBH_ERROR_BIND_FAILURE, err);
				mysql_stmt_close(my_stmt);
				return nullptr;
			}

			if(mysql_stmt_execute(my_stmt)) {
				std::string err = mysql_stmt_error(my_stmt);
				SetError(DBH_ERROR_STMT_FAILURE, err);
				mysql_stmt_close(my_stmt);
				return nullptr;
			}
		} else {
			if(mysql_stmt_execute(my_stmt)) {
				std::string err = mysql_stmt_error(my_stmt);
				SetError(DBH_ERROR_STMT_FAILURE, err);
				mysql_stmt_close(my_stmt);
				return nullptr;
			}		
		}

		std::unique_ptr<ResultSet> res(DBI::MySQLDatabaseHandle::_internal_results_from_mysql_stmt(my_stmt));
		mysql_stmt_close(my_stmt);
		return res;
	}
}

std::unique_ptr<DBI::StatementHandle> DBI::MySQLDatabaseHandle::Prepare(std::string stmt) {
	assert(handle != nullptr);
	MYSQL_STMT *my_stmt = mysql_stmt_init(handle);
	if(mysql_stmt_prepare(my_stmt, stmt.c_str(), static_cast<unsigned long>(stmt.length()))) {
		std::string err = mysql_stmt_error(my_stmt);
		SetError(DBH_ERROR_PREPARE_FAILURE, err);
		mysql_stmt_close(my_stmt);
		return nullptr;
	}

	std::unique_ptr<StatementHandle> sth(new MySQLStatementHandle(my_stmt));
	return sth;
}

bool DBI::MySQLDatabaseHandle::Ping() {
	assert(handle != nullptr);
	if(mysql_ping(handle)) {
		SetError(DBH_ERROR_PING_CONNECTION, "Pinging the MySQL connection failed.");
		return false;
	}

	return true;
}

bool DBI::MySQLDatabaseHandle::Begin() {
	assert(handle != nullptr);
	if(mysql_autocommit(handle, 0)) {
		SetError(DBH_ERROR_BEGIN_FAILURE, "DBI::MySQLDatabaseHandle::Begin() failed.");
		return false;
	}

	return true;
}

bool DBI::MySQLDatabaseHandle::Commit() {
	assert(handle != nullptr);
	if(mysql_commit(handle)) {
		mysql_autocommit(handle, 1);
		SetError(DBH_ERROR_COMMIT_FAILURE, "DBI::MySQLDatabaseHandle::Commit() failed.");
		return false;
	}

	mysql_autocommit(handle, 1);
	return true;
}

bool DBI::MySQLDatabaseHandle::Rollback() {
	assert(handle != nullptr);
	if(mysql_rollback(handle)) {
		mysql_autocommit(handle, 1);
		SetError(DBH_ERROR_ROLLBACK_FAILURE, "DBI::MySQLDatabaseHandle::Rollback() failed.");
		return false;
	}

	mysql_autocommit(handle, 1);
	return true;
}

std::unique_ptr<DBI::ResultSet> DBI::MySQLDatabaseHandle::_internal_results_from_mysql_stmt(MYSQL_STMT* statement) {
	assert(statement != nullptr);
	MYSQL_RES *res = mysql_stmt_result_metadata(statement);
	std::vector<std::unique_ptr<char>> buffers;
	std::unique_ptr<MYSQL_BIND> results(nullptr);
	std::unique_ptr<my_bool> is_null(nullptr);
	std::unique_ptr<my_bool> err(nullptr);
	std::unique_ptr<unsigned long> len(nullptr);
	std::vector<std::string> field_names;
	uint32_t fields = 0;

	if(res) {
		fields = mysql_num_fields(res);
		if(fields != 0) {
			buffers.resize(fields);
			results.reset(new MYSQL_BIND[fields]);
			is_null.reset(new my_bool[fields]);
			err.reset(new my_bool[fields]);
			len.reset(new unsigned long[fields]);
			memset(results.get(), 0, sizeof(MYSQL_BIND) * fields);
			memset(is_null.get(), 0, sizeof(my_bool) * fields);
			memset(err.get(), 0, sizeof(my_bool) * fields);
			memset(len.get(), 0, sizeof(unsigned long) * fields);

			MYSQL_FIELD *f = nullptr;
			uint32_t i = 0;
			while(f = mysql_fetch_field(res)) {
				field_names.push_back(std::string(f->name));
				
				buffers[i].reset(new char[f->length]);
				results.get()[i].buffer_type = MYSQL_TYPE_STRING;
				results.get()[i].buffer = buffers[i].get();
				results.get()[i].buffer_length = f->length;
				results.get()[i].is_null = &is_null.get()[i];
				results.get()[i].error = &err.get()[i];
				results.get()[i].length = &len.get()[i];
				++i;
			}

			mysql_stmt_bind_result(statement, results.get());
		}
		mysql_free_result(res);
	}

	if(mysql_stmt_store_result(statement)) {
		return nullptr;
	}

	std::list<DBI::ResultSet::Row> rows;
	while(!mysql_stmt_fetch(statement)) {
		DBI::ResultSet::Row row;

		for(uint32_t i = 0; i < fields; ++i) {
			std::string val;
			if(len.get()[i] > 0) {
				val.assign(buffers[i].get(), len.get()[i]);
			}

			row[field_names[i]] = DBI::ResultSet::FieldData(is_null.get()[i] ? true : false, err.get()[i] ? true : false, val);
		}
		rows.push_back(row);
	}

	std::unique_ptr<ResultSet> rs(new MySQLResultSet(field_names, rows,
		static_cast<unsigned long>(mysql_stmt_affected_rows(statement)),
		static_cast<unsigned long>(mysql_stmt_insert_id(statement))));
	return rs;
}
