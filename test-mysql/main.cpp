#include <stdio.h>
#include "../dbi/dbi.h"
#include "../dbi/dbh.h"

int main() {
	DBI::DatabaseAttributes attr;
	attr["mysql_reconnect"] = "1";
	attr["mysql_server_side_prepare"]  = "1";

	DBI::DatabaseHandle *dbh = DBI::DatabaseInterface::Instance()->Connect("mysql", "eqdb", "127.0.0.1", "root", "", attr);
	if(dbh) {
		printf("Connected...\n");
	} else {
		printf("Could not connect...\n");
		getchar();
		return 0;
	}

	if(!dbh->Do("REPLACE INTO variables (varname, value, information) VALUES(?, ?, ?)", 
		std::string("TestArgument"), 
		275.2f, 
		std::string("Some information about this shit."))) {
		printf("dbh->Do error: %s\n", dbh->ErrorMessage());
	}

	getchar();
	return 0;
}
