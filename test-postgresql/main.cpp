#include <stdio.h>
#include "../dbi/dbi.h"
#include "../dbi/dbh.h"
#include "../dbi/sth.h"
#include "../dbi/rs.h"

int main() {
	DBI::DatabaseAttributes attr;
	auto dbh = DBI::DatabaseInterface::Instance()->Connect("postgresql", "eqdb", "127.0.0.1", "eqdb", "password", attr);
	if(dbh) {
		printf("Connected...\n");
	} else {
		printf("Could not connect...\n");
		getchar();
		return 0;
	}

	char *tdata = "hello\0world\0"; // len = 12
	char *sql = "INSERT INTO btest(test_value) VALUES(?)";
	
	std::string mstr;
	mstr.assign(tdata, 12);
	
	auto rs = dbh->Do("insert into btest(test_value) VALUES(?)", mstr);
	if(rs) {
		printf("Affected rows: %d\n", rs->AffectedRows());	
	}
	
	rs = dbh->Do("select * from btest");
	if(rs) {
		auto iter = rs->Rows().begin();
		while(iter != rs->Rows().end()) {
			auto row = (*iter);
			std::string v = row["test_value"].value;
			printf("Retrieved: %d bytes\n", v.length());
			++iter;
		}	
	}

	/*auto res = dbh->Do("INSERT INTO variables(varname, value, information) VALUES(?, ?, ?)", std::string("MOTD"),
		std::string("Welcome to ProjectEQ! www.peqtgc.com Please use the forums to report bugs or other problems: www.peqtgc.com/phpBB2/"
		" To activate a forum or login account, see the posts entitled \"Forum Activation\" and \"PEQ Login Server\" under the General section"
		" of the forums. We are setup to use the *ORIGINAL NEKTULOS* for Titanium/6.2 clients only Please see the forum post entitled "
		"\"About new zones\" also under the General section for further info."),
		std::string());
	if(!res) {
		printf("Error: %s\n", dbh->ErrorMessage().c_str());
	} else {
		printf("affected: %d\n", res->AffectedRows());
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

	auto sth = dbh->Prepare("SELECT * FROM variables WHERE varname=?");
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

		printf("execute again\n");
		rs = sth->Execute((const char*)"MOTD");
		iter = rs->Rows().begin();
		while(iter != rs->Rows().end()) {
			auto row = (*iter);
			printf("\n");
			
			auto fields = rs->Fields();
			for(int i = 0; i < row.size(); ++i) {
				printf("null = %s: %s\n", row[fields[i]].is_null ? "true" : "false", row[fields[i]].value.c_str());
			}
			++iter;
		}
	}*/

	getchar();
	return 0;
}
