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
#ifndef DBI__DBI_H
#define DBI__DBI_H

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "any.h"
#include "dbi-error.h"

namespace DBI
{

typedef std::map<std::string, std::string> DatabaseAttributes;
typedef std::vector<DBI::Any> StatementArguments;

class DatabaseHandle;

class DatabaseInterface : public ErrorHandler
{
public:
	~DatabaseInterface();

	static DatabaseInterface* Instance();

	void Drivers(std::list<std::string> &drivers);

	std::unique_ptr<DatabaseHandle> Connect(std::string driver, std::string dbname, std::string host,
		std::string username, std::string auth, DatabaseAttributes &attr);
private:
	DatabaseInterface();
	DatabaseInterface(const DatabaseInterface&);
	DatabaseInterface& operator=(const DatabaseInterface&);
	
	static DatabaseInterface* _instance;
};

}

#endif
