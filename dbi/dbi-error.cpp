#include "dbi-error.h"
#include <string.h>

void DBI::ErrorHandler::SetError(DBI::DBIErrorCode code, std::string msg) {
	error_code = code;
	error_message = msg;
}
