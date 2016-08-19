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
#ifndef DBI__STH_H
#define DBI__STH_H

namespace DBI
{

class ResultSet;

class StatementHandle
{
public:
	StatementHandle() { }
	virtual ~StatementHandle() { }
	
	std::unique_ptr<ResultSet> Execute() {
		return InternalExecute();
	}

	template<typename T, typename... Args>
	std::unique_ptr<ResultSet> Execute(T value, Args... args)
	{
		BindArg(value, 1);
		return _Execute(2, args...);
	}

protected:
	std::unique_ptr<ResultSet> _Execute(int i) {
		return InternalExecute();
	}

	template<typename T, typename... Args>
	std::unique_ptr<ResultSet> _Execute(int i, T value, Args... args)
	{
		BindArg(value, i);
		return _Execute(i + 1, args...);
	}

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
	virtual std::unique_ptr<ResultSet> InternalExecute() = 0;
};

}

#endif
