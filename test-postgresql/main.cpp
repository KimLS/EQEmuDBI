#include <stdio.h>
#include "../dbi/dbi.h"
#include "../dbi/dbh.h"
#include "../dbi/sth.h"
#include "../dbi/rs.h"

int main() {
	DBI::DatabaseAttributes attr;
	attr["mysql_reconnect"] = "1";
	attr["mysql_server_side_prepare"]  = "1";

	auto dbh = DBI::DatabaseInterface::Instance()->Connect("postgresql", "eqdb", "127.0.0.1", "eqdb", "password", attr);
	if(dbh) {
		printf("Connected...\n");
	} else {
		printf("Could not connect...\n");
		getchar();
		return 0;
	}

	auto res = dbh->Do("INSERT INTO variables(varname, value, information) VALUES(?, ?, ?)", std::string("MOTD"),
		std::string("Welcome to ProjectEQ! www.peqtgc.com Please use the forums to report bugs or other problems: www.peqtgc.com/phpBB2/"
		" To activate a forum or login account, see the posts entitled \"Forum Activation\" and \"PEQ Login Server\" under the General section"
		" of the forums. We are setup to use the *ORIGINAL NEKTULOS* for Titanium/6.2 clients only Please see the forum post entitled "
		"\"About new zones\" also under the General section for further info."),
		std::string());
	if(!res) {
		printf("Error: %s\n", dbh->ErrorMessage().c_str());
	}

	//res = dbh->Do("SELECT * FROM variables WHERE varname=?", (const char*)"MOTD");
	//if(res) {
	//	auto iter = res->Rows().begin();
	//	while(iter != res->Rows().end()) {
	//		auto row = (*iter);
	//		printf("\n");
	//		
	//		auto fields = res->Fields();
	//		for(int i = 0; i < row.size(); ++i) {
	//			printf("%s: %s\n", fields[i].c_str(), row[fields[i]].value.c_str());
	//		}
	//		++iter;
	//	}
	//} else {
	//	printf("Error: %s\n", dbh->ErrorMessage().c_str());
	//}

	auto sth = dbh->Prepare("SELECT * FROM variables WHERE varname=?", "Select Variable");
	if(sth) {
		auto rs = sth->Execute((const char*)"MOTD");
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
