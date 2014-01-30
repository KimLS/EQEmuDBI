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
	//if(mysql_autocommit(handle, 0)) {
	//	SetError(DBH_ERROR_BEGIN_FAILURE, "DBI::MySQLDatabaseHandle::Begin() failed.");
	//	return false;
	//}

	return true;
}

bool DBI::PGDatabaseHandle::Commit() {
	assert(handle != nullptr);
	//if(mysql_commit(handle)) {
	//	mysql_autocommit(handle, 1);
	//	SetError(DBH_ERROR_COMMIT_FAILURE, "DBI::MySQLDatabaseHandle::Commit() failed.");
	//	return false;
	//}
	//
	//mysql_autocommit(handle, 1);
	return true;
}

bool DBI::PGDatabaseHandle::Rollback() {
	assert(handle != nullptr);
	//if(mysql_rollback(handle)) {
	//	mysql_autocommit(handle, 1);
	//	SetError(DBH_ERROR_ROLLBACK_FAILURE, "DBI::MySQLDatabaseHandle::Rollback() failed.");
	//	return false;
	//}
	//
	//mysql_autocommit(handle, 1);
	return true;
}
