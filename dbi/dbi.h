#ifndef DBI__DBI_H
#define DBI__DBI_H

#ifdef _WIN32
#define DBI_EXPORT __declspec(dllexport)
#else
#define DBI_EXPORT 
#endif

#include <string>
#include <vector>
#include <list>
#include <map>
#include "any.h"

#define MAX_DBI_ERROR_MSG_LEN 2048

namespace DBI
{

typedef std::map<std::string, std::string> DatabaseAttributes;
typedef std::vector<DBI::Any> StatementArguments;

class DatabaseHandle;

enum DatabaseInterfaceErrorCode
{
	DBI_ERROR_NONE = 0,
	DBI_ERROR_DRIVER_NOT_FOUND,
	DBI_ERROR_FAILED_TO_CONNECT
};

class DBI_EXPORT DatabaseInterface
{
public:
	~DatabaseInterface();

	static DatabaseInterface* Instance();

	void Drivers(std::list<std::string> &drivers);

	DatabaseHandle* Connect(std::string driver, std::string dbname, std::string host,
		std::string username, std::string auth, DatabaseAttributes &attr);

	bool Error() const { return error_code != DBI_ERROR_NONE; };
	const char* ErrorMessage() const { return error_message; }
	const DatabaseInterfaceErrorCode ErrorCode() const { return error_code; }
private:
	DatabaseInterface();
	DatabaseInterface(const DatabaseInterface&);
	DatabaseInterface& operator=(const DatabaseInterface&);
	void SetError(DatabaseInterfaceErrorCode code, const char *msg);

	static DatabaseInterface* _instance;
	char error_message[MAX_DBI_ERROR_MSG_LEN];
	DatabaseInterfaceErrorCode error_code;
};

}

#endif
