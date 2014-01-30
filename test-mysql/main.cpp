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
		sth->Execute(std::string("MOTD"));
		DBI::ResultSet *rs = sth->Results();
		auto iter = rs->RowsByIndex().begin();
		while(iter != rs->RowsByIndex().end()) {
			auto row = (*iter);
			printf("\n");
			for(int i = 0; i < row.size(); ++i) {
				printf("null = %s: %s\n", row[i].first ? "true" : "false", row[i].second.c_str());
			}
			++iter;
		}
	}

	//if(sth) {
	//	sth->Execute(std::string("TestArgument"), 275.2f, std::string("Some information about this shit."));
	//}

	//DBI::StatementHandle *sth = dbh->Prepare("REPLACE INTO variables (varname, value, information) VALUES(?, ?, ?)");
	//if(sth) {
	//	sth->Execute(std::string("TestArgument"), 275.2f, std::string("Some information about this shit."));
	//}

	//if(!dbh->Do("REPLACE INTO variables (varname, value, information) VALUES(?, ?, ?)", 
	//	std::string("TestArgument"), 
	//	275.2f, 
	//	std::string("Some information about this shit."))) {
	//	printf("dbh->Do error: %s\n", dbh->ErrorMessage());
	//}

	getchar();
	return 0;
}
