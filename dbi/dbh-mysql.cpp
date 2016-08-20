#include "dbh-mysql.h"

#ifndef SOCKET
#define SOCKET int
#endif
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>
#undef SOCKET

#include "sth-mysql.h"

DBI::MySQLDatabaseHandle::MySQLDatabaseHandle()
{
	m_handle = nullptr;
	m_do_stmt = nullptr;
}

DBI::MySQLDatabaseHandle::~MySQLDatabaseHandle()
{
	ClearBindParams();
	Disconnect();
}

void DBI::MySQLDatabaseHandle::Connect(std::string dbname, std::string host, std::string username, std::string auth, DatabaseAttributes &attr)
{
	if(m_handle) {
		return;
	}
	
	m_handle = mysql_init(m_handle);
	if(!m_handle) {
		throw std::runtime_error("Error in init of MySQL handle");
	}
	
	unsigned int client_flag = 0;
	auto iter = attr.find("mysql_init_command");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_INIT_COMMAND, iter->second.c_str());
	}
	
	iter = attr.find("mysql_compress");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_OPT_COMPRESS, nullptr);
	}
	
	iter = attr.find("mysql_connect_timeout");
	if(iter != attr.end()) {
		int t = std::stoi(iter->second);
		mysql_options(m_handle, MYSQL_OPT_CONNECT_TIMEOUT, &t);
	}
	
	iter = attr.find("mysql_local_infile");
	if(iter != attr.end()) {
		unsigned int t = static_cast<unsigned int>(std::stoi(iter->second));
		mysql_options(m_handle, MYSQL_OPT_LOCAL_INFILE, &t);
	}
	
	iter = attr.find("mysql_named_pipe");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_OPT_RECONNECT, nullptr);
	}
	
	iter = attr.find("mysql_protocol");
	if(iter != attr.end()) {
		unsigned int t = static_cast<unsigned int>(std::stoi(iter->second));
		mysql_options(m_handle, MYSQL_OPT_PROTOCOL, &t);
	}
	
	iter = attr.find("mysql_read_timeout");
	if(iter != attr.end()) {
		unsigned int t = static_cast<unsigned int>(std::stoi(iter->second));
		mysql_options(m_handle, MYSQL_OPT_READ_TIMEOUT, &t);
	}
	
	iter = attr.find("mysql_reconnect");
	if(iter != attr.end()) {
		my_bool t = static_cast<my_bool>(std::stoi(iter->second));
		mysql_options(m_handle, MYSQL_OPT_RECONNECT, &t);
	}
	
	iter = attr.find("mysql_ssl_verify_server_cert");
	if(iter != attr.end()) {
		my_bool t = static_cast<my_bool>(std::stoi(iter->second));
		mysql_options(m_handle, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &t);
	}
	
	iter = attr.find("mysql_use_result");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_OPT_USE_RESULT, nullptr);
	}
	
	iter = attr.find("mysql_write_timeout");
	if(iter != attr.end()) {
		unsigned int t = static_cast<unsigned int>(std::stoi(iter->second));
		mysql_options(m_handle, MYSQL_OPT_WRITE_TIMEOUT, &t);
	}
	
	iter = attr.find("mysql_read_default_file");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_READ_DEFAULT_FILE, iter->second.c_str());
	}
	
	iter = attr.find("mysql_read_default_group");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_READ_DEFAULT_GROUP, iter->second.c_str());
	}
	
	iter = attr.find("mysql_report_data_truncation");
	if(iter != attr.end()) {
		my_bool t = static_cast<my_bool>(std::stoi(iter->second));
		mysql_options(m_handle, MYSQL_REPORT_DATA_TRUNCATION, &t);
	}
	
	iter = attr.find("mysql_secure_auth");
	if(iter != attr.end()) {
		my_bool t = static_cast<my_bool>(std::stoi(iter->second));
		mysql_options(m_handle, MYSQL_SECURE_AUTH, &t);
	}
	
	iter = attr.find("mysql_charset_dir");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_SET_CHARSET_DIR, iter->second.c_str());
	}
	
	iter = attr.find("mysql_charset_name");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_SET_CHARSET_NAME, iter->second.c_str());
	}
	
	iter = attr.find("mysql_shared_memory_base_name");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_SHARED_MEMORY_BASE_NAME, iter->second.c_str());
	}
	
	iter = attr.find("mysql_read_default_group");
	if(iter != attr.end()) {
		mysql_options(m_handle, MYSQL_READ_DEFAULT_GROUP, iter->second.c_str());
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
	
			mysql_ssl_set(m_handle,
				client_key.empty() ? nullptr : client_key.c_str(),
				client_cert.empty() ? nullptr : client_cert.c_str(),
				ca_file.empty() ? nullptr : ca_file.c_str(),
				ca_path.empty() ? nullptr : ca_path.c_str(),
				cipher.empty() ? nullptr : cipher.c_str());
	
			mysql_options(m_handle, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &verify_true);
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
	
	MYSQL* result = mysql_real_connect(m_handle, host.c_str(), username.c_str(), auth.c_str(), dbname.c_str(), port,
		socket.empty() ? nullptr : socket.c_str(), client_flag);
	
	if(!result) {
		std::string err = "Could not connect to MySQL database: ";
		err += mysql_error(m_handle);
		Disconnect();
		throw std::runtime_error(err);
	}
}

void DBI::MySQLDatabaseHandle::Disconnect()
{
	if (!m_handle) {
		return;
	}

	mysql_close(m_handle);
	m_handle = nullptr;
}

std::unique_ptr<DBI::StatementHandle> DBI::MySQLDatabaseHandle::Prepare(std::string stmt)
{
	auto *s = mysql_stmt_init(m_handle);
	if (mysql_stmt_prepare(s, stmt.c_str(), static_cast<unsigned long>(stmt.length()))) {
		std::string err = "Prepare failure: ";
		err += mysql_stmt_error(s);
		mysql_stmt_close(s);

		throw std::runtime_error(err);
	}

	return std::unique_ptr<StatementHandle>(new MySQLStatementHandle(m_handle, s));
}

void DBI::MySQLDatabaseHandle::Ping()
{
	if(mysql_ping(m_handle)) {
		throw std::runtime_error("Pinging the MySQL connection failed.");
	}
}

void DBI::MySQLDatabaseHandle::Begin()
{
	if(mysql_autocommit(m_handle, 0)) {
		throw std::runtime_error("DBI::MySQLDatabaseHandle::Begin() failed.");
	}
}

void DBI::MySQLDatabaseHandle::Commit()
{
	if(mysql_commit(m_handle)) {
		mysql_autocommit(m_handle, 1);
		throw std::runtime_error("DBI::MySQLDatabaseHandle::Commit() failed.");
	}
	
	mysql_autocommit(m_handle, 1);
}

void DBI::MySQLDatabaseHandle::Rollback()
{
	if(mysql_rollback(m_handle)) {
		mysql_autocommit(m_handle, 1);
		throw std::runtime_error("DBI::MySQLDatabaseHandle::Rollback() failed.");
	}
	
	mysql_autocommit(m_handle, 1);
}

void DBI::MySQLDatabaseHandle::BindArg(int8_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_TINY;
	auto p = new int8_t(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(uint8_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_TINY;
	auto p = new uint8_t(v);
	bind.buffer = p;
	bind.is_unsigned = 1;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(int16_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_SHORT;
	auto p = new int16_t(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(uint16_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_SHORT;
	auto p = new uint16_t(v);
	bind.buffer = p;
	bind.is_unsigned = 1;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(int32_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_LONG;
	auto p = new int32_t(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(uint32_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_LONG;
	auto p = new uint32_t(v);
	bind.buffer = p;
	bind.is_unsigned = 1;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(int64_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_LONGLONG;
	auto p = new int64_t(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(uint64_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_LONGLONG;
	auto p = new uint64_t(v);
	bind.buffer = p;
	bind.is_unsigned = 1;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(float v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_FLOAT;
	auto p = new float(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(double v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_DOUBLE;
	auto p = new double(v);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(const std::string &v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_STRING;

	auto p = new char[v.length()];
	memcpy(p, v.c_str(), v.length());
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	bind.buffer_length = static_cast<unsigned long>(v.length());
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(const char *v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_STRING;

	auto v_length = strlen(v);
	auto p = new char[v_length];
	memcpy(p, v, v_length);
	bind.buffer = p;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	bind.buffer_length = static_cast<unsigned long>(v_length);
	m_bind_params.push_back(bind);
}

void DBI::MySQLDatabaseHandle::BindArg(std::nullptr_t v)
{
	if (m_do_stmt == nullptr) {
		return;
	}

	MYSQL_BIND bind;
	memset(&bind, 0, sizeof(bind));
	bind.buffer_type = MYSQL_TYPE_NULL;
	bind.buffer = nullptr;
	bind.is_unsigned = 0;
	bind.is_null = nullptr;
	bind.length = 0;
	m_bind_params.push_back(bind);
}

std::unique_ptr<DBI::ResultSet> DBI::MySQLDatabaseHandle::ExecuteDo()
{
	if (m_bind_params.size() > 0) {
		if (mysql_stmt_bind_param(m_do_stmt, &m_bind_params[0])) {
			std::string err = "Do execute failure: ";
			err += mysql_stmt_error(m_do_stmt);
			mysql_stmt_close(m_do_stmt);
			m_do_stmt = nullptr;
			throw std::runtime_error(err);
		}
	}

	if (mysql_stmt_execute(m_do_stmt)) {
		std::string err = "Do execute failure: ";
		err += mysql_stmt_error(m_do_stmt);
		mysql_stmt_close(m_do_stmt);
		m_do_stmt = nullptr;
		throw std::runtime_error(err);
	}

	MYSQL_RES *res = mysql_stmt_result_metadata(m_do_stmt);
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
			while((f = mysql_fetch_field(res)) != nullptr) {
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
	
			mysql_stmt_bind_result(m_do_stmt, results.get());
		}
		mysql_free_result(res);
	}

	if(mysql_stmt_store_result(m_do_stmt)) {
		return nullptr;
	}

	std::list<DBI::ResultSet::Row> rows;
	while(!mysql_stmt_fetch(m_do_stmt)) {
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

	ResultSet *rs = new ResultSet(field_names, rows, static_cast<unsigned long>(mysql_stmt_affected_rows(m_do_stmt)));

	mysql_stmt_close(m_do_stmt);
	m_do_stmt = nullptr;
	return std::unique_ptr<ResultSet>(rs);
}

void DBI::MySQLDatabaseHandle::InitDo(const std::string &stmt)
{
	if (m_do_stmt == nullptr) {
		m_do_stmt = mysql_stmt_init(m_handle);
		if (mysql_stmt_prepare(m_do_stmt, stmt.c_str(), static_cast<unsigned long>(stmt.length()))) {
			std::string err = "Do failure: ";
			err += mysql_stmt_error(m_do_stmt);
			mysql_stmt_close(m_do_stmt);
			m_do_stmt = nullptr;
			throw std::runtime_error(err);
		}

		ClearBindParams();
	}
}

void DBI::MySQLDatabaseHandle::ClearBindParams()
{
	for (auto &bind : m_bind_params) {
		if (bind.buffer_type == MYSQL_TYPE_STRING) {
			delete[] bind.buffer;
			continue;
		}

		if (bind.buffer_type == MYSQL_TYPE_NULL) {
			continue;
		}

		delete bind.buffer;
	}

	m_bind_params.clear();
}
