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
#include "sth-pg.h"
#include "rs.h"
#include <stdint.h>
#include <assert.h>
#include <memory>
#include <libpq-fe.h>

DBI::PGStatementHandle::PGStatementHandle(PGconn *conn_, std::string name_) : conn(conn_), name(name_) {
}

DBI::PGStatementHandle::~PGStatementHandle() {
}

std::unique_ptr<DBI::ResultSet> DBI::PGStatementHandle::Execute() {
	StatementArguments args;
	return Execute(args);
}

std::unique_ptr<DBI::ResultSet> DBI::PGStatementHandle::Execute(StatementArguments &args) {
	assert(conn != nullptr);
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from bool arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint8_t arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int8_t arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint16_t arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int16_t arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint32_t arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int32_t arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from uint64_t arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from int64_t arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from float arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from double arg in DBI::PGStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(t.type() == typeid(std::string)) {
				try {
					std::string v = DBI::any_cast<std::string>(t);
					size_t len = v.length();
					size_t clen = strlen(v.c_str());
					
					if(len != clen) {
						size_t conv_len = 0;
						unsigned char* converted = PQescapeByteaConn(conn, (const unsigned char*)v.c_str(), len, &conv_len);
						std::shared_ptr<char> t(new char[conv_len + 1]);
						paramValues.get()[i] = t.get();
						strncpy(t.get(), (const char*)converted, conv_len);
						t.get()[conv_len] = 0;
						paramSave.push_back(t);
						PQfreemem(converted);
					} else {
						std::shared_ptr<char> t(new char[len + 1]);
						paramValues.get()[i] = t.get();
						strncpy(t.get(), v.c_str(), len);
						t.get()[len] = 0;
						paramSave.push_back(t);
					}
				} catch(DBI::bad_any_cast) {
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from std::string arg in DBI::PGStatementHandle::Execute(args).");
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
					SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from const char* arg in DBI::PGStatementHandle::Execute(args).");
					return nullptr;
				}
			} else if(!t.empty() && t.type() != typeid(std::nullptr_t)) {
				SetError(DBH_ERROR_INVALID_ARGS, "Could not convert from unknown arg in DBI::PGStatementHandle::Execute(args).");
				return nullptr;
			}
		}
	}

	PGresult *res = PQexecPrepared(conn, name.c_str(), (int)nParams, paramValues.get(), nullptr, nullptr, 0);
	
	if(res) {
		std::unique_ptr<ResultSet> rs = DBI::PGDatabaseHandle::_internal_results_from_postgresql(res);
		if(rs) {
			PQclear(res);
			return rs;
		}
	
		std::string err = PQresultErrorMessage(res);
		SetError(STH_ERROR_STMT_FAILURE, err);
		PQclear(res);
	}
	return nullptr;
}
