#include <stdio.h>
#include "../dbi/dbi.h"
#include "../dbi/dbh.h"
#include "../dbi/sth.h"
#include "../dbi/rs.h"

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

	DBI::StatementHandle *sth = dbh->Prepare("SELECT * FROM variables WHERE varname=?");
	if(sth) {
		sth->Execute((const char*)"MOTD");
		DBI::ResultSet *rs = sth->Results();
		auto iter = rs->Rows().begin();
		while(iter != rs->Rows().end()) {
			auto row = (*iter);
			printf("\n");
			
			auto fields = rs->Fields();
			for(int i = 0; i < row.size(); ++i) {
				printf("null = %s: %s\n", row[fields[i]].is_null ? "true" : "false", row[fields[i]].value.c_str());
			}
			++iter;
		}
	}

	getchar();
	return 0;
}
