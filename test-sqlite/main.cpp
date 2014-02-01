#include <stdio.h>
#include "../dbi/dbi.h"
#include "../dbi/dbh.h"
#include "../dbi/sth.h"
#include "../dbi/rs.h"

int main() {
	DBI::DatabaseAttributes attr;
	attr["mysql_reconnect"] = "1";
	attr["mysql_server_side_prepare"]  = "1";

	auto dbh = DBI::DatabaseInterface::Instance()->Connect("sqlite", "test.db", "", "", "", attr);
	if(dbh) {
		printf("Connected...\n");
	} else {
		printf("Could not connect...\n");
		getchar();
		return 0;
	}

	auto rs = dbh->Do("update variables set information=? where varname=?", (const char*)"some crazy crazy info", (const char*)"MOTD");

	//rs = dbh->Do("select * from variables where varname=?", (const char*)"MOTD");
	//if(rs) {
	//	auto iter = rs->Rows().begin();
	//	while(iter != rs->Rows().end()) {
	//		auto row = (*iter);
	//		printf("\n");
	//		
	//		auto fields = rs->Fields();
	//		for(int i = 0; i < row.size(); ++i) {
	//			printf("%s: %s\n", fields[i].c_str(), row[fields[i]].value.c_str());
	//		}
	//		++iter;
	//	}
	//}

	auto sth = dbh->Prepare("SELECT * FROM variables WHERE varname=?");
	if(sth) {
		auto rs = sth->Execute((const char*)"MOTD");
		if(rs) {
			auto iter = rs->Rows().begin();
			while(iter != rs->Rows().end()) {
				auto row = (*iter);
				printf("\n");
				
				auto fields = rs->Fields();
				for(int i = 0; i < row.size(); ++i) {
					printf("%s null = %s: %s\n", fields[i].c_str(), row[fields[i]].is_null ? "true" : "false", row[fields[i]].value.c_str());
				}
				++iter;
			}
		}

		printf("Again:\n");
		rs = sth->Execute((const char*)"MOTD");
		if(rs) {
			auto iter = rs->Rows().begin();
			while(iter != rs->Rows().end()) {
				auto row = (*iter);
				printf("\n");
				
				auto fields = rs->Fields();
				for(int i = 0; i < row.size(); ++i) {
					printf("%s null = %s: %s\n", fields[i].c_str(), row[fields[i]].is_null ? "true" : "false", row[fields[i]].value.c_str());
				}
				++iter;
			}
		}
	}

	getchar();
	return 0;
}
