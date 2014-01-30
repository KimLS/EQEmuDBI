#ifndef DBI__DBI_H
#define DBI__DBI_H

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

	DatabaseHandle* Connect(std::string driver, std::string dbname, std::string host,
		std::string username, std::string auth, DatabaseAttributes &attr);
private:
	DatabaseInterface();
	DatabaseInterface(const DatabaseInterface&);
	DatabaseInterface& operator=(const DatabaseInterface&);
	
	static DatabaseInterface* _instance;
};

}

#endif
