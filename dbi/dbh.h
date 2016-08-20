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
#ifndef DBI__DBH_H
#define DBI__DBH_H

#include <stdexcept>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <map>

#include "rs.h"
#include "sth.h"

namespace DBI
{
	typedef std::map<std::string, std::string> DatabaseAttributes;
	class StatementHandle;
	class ResultSet;
	class DatabaseHandle
	{
	public:
		DatabaseHandle() { }
		virtual ~DatabaseHandle() { }
	
		virtual void Connect(std::string dbname, std::string host, std::string username,
			std::string auth, DatabaseAttributes &attr) = 0;
		virtual void Disconnect() = 0;

		virtual std::unique_ptr<StatementHandle> Prepare(std::string stmt) = 0;

		virtual void Ping() = 0;
		virtual void Begin() = 0;
		virtual void Commit() = 0;
		virtual void Rollback() = 0;

		std::unique_ptr<ResultSet> Do(const std::string &stmt) {
			InitDo(stmt);
			return ExecuteDo();
		}

		template<typename T, typename... Args>
		std::unique_ptr<ResultSet> Do(const std::string &stmt, T value, Args... args)
		{
			InitDo(stmt);
			BindArg(value, 1);
			return _Do(2, args...);
		}

	protected:
		std::unique_ptr<ResultSet> _Do(int i) {
			return ExecuteDo();
		}

		template<typename T, typename... Args>
		std::unique_ptr<ResultSet> _Do(int i, T value, Args... args)
		{
			BindArg(value, i);
			return _Do(i + 1, args...);
		}

		virtual void BindArg(bool v, int i) = 0;
		virtual void BindArg(int8_t v, int i) = 0;
		virtual void BindArg(uint8_t v, int i) = 0;
		virtual void BindArg(int16_t v, int i) = 0;
		virtual void BindArg(uint16_t v, int i) = 0;
		virtual void BindArg(int32_t v, int i) = 0;
		virtual void BindArg(uint32_t v, int i) = 0;
		virtual void BindArg(int64_t v, int i) = 0;
		virtual void BindArg(uint64_t v, int i) = 0;
		virtual void BindArg(float v, int i) = 0;
		virtual void BindArg(double v, int i) = 0;
		virtual void BindArg(const std::string &v, int i) = 0;
		virtual void BindArg(const char *v, int i) = 0;
		virtual void BindArg(std::nullptr_t v, int i) = 0;
		virtual std::unique_ptr<ResultSet> ExecuteDo() = 0;
		virtual void InitDo(const std::string& stmt) = 0;
	};
}

#endif
