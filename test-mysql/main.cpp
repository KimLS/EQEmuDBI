#include <stdio.h>
#include "../dbi/dbi.h"
#include "../dbi/dbh.h"
#include "../dbi/sth.h"
#include "../dbi/rs-mysql.h"

int main() {
	DBI::DatabaseAttributes attr;
	attr["mysql_reconnect"] = "1";

	auto dbh = DBI::DatabaseInterface::Instance()->Connect("mysql", "eqdb", "127.0.0.1", "root", "", attr);
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

	/*auto rs = dbh->Do("UPDATE variables SET information = ? WHERE varname = ?", 
		(const char*)"Some really crazy info here...", (const char*)"MOTD");
	if(rs) {
		printf("Affected rows: %d\n", ((DBI::MySQLResultSet*)rs.get())->AffectedRows());
	}

	auto sth = dbh->Prepare("SELECT * FROM variables WHERE varname=?");
	if(sth) {
		auto rs = sth->Execute((const char*)"MOTD");
		auto iter = rs->Rows().begin();
		while(iter != rs->Rows().end()) {
			auto row = (*iter);
			printf("\n");
			
			auto fields = rs->Fields();
			for(int i = 0; i < row.size(); ++i) {
				printf("%s: %s\n", fields[i].c_str(), row[fields[i]].value.c_str());
			}
			++iter;
		}
	}*/

	getchar();
	return 0;
}
	