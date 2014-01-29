#include "dbh.h"

void DBI::DatabaseHandle::SetError(DatabaseHandleErrorCode code, const char *msg) {
	error_code = code;

	size_t msg_len = strlen(msg);
	if(msg_len < MAX_DBI_ERROR_MSG_LEN) {
		strcpy(error_message, msg);
		error_message[msg_len] = '\0';
	} else {
		strncpy(error_message, msg, MAX_DBI_ERROR_MSG_LEN - 1);
		error_message[MAX_DBI_ERROR_MSG_LEN] = '\0';
	}
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0) {
	StatementArguments args;
	args.push_back(arg0);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7, DBI::Any arg8) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	args.push_back(arg8);
	return Do(stmt, args);
}

bool DBI::DatabaseHandle::Do(std::string stmt, DBI::Any arg0, DBI::Any arg1, DBI::Any arg2, DBI::Any arg3, DBI::Any arg4, DBI::Any arg5,
	DBI::Any arg6, DBI::Any arg7, DBI::Any arg8, DBI::Any arg9) {
	StatementArguments args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	args.push_back(arg8);
	args.push_back(arg9);
	return Do(stmt, args);
}
