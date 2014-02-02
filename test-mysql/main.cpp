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

	char *tdata = "hello\0world\0";
	std::string mstr;
	mstr.assign(tdata, 12);
	
	auto rs = dbh->Do("INSERT INTO btest(test_value) VALUES(?)", mstr);
	if(rs) {
		printf("Affected Rows: %d\n", rs->AffectedRows());	
	}
	
	rs = dbh->Do("SELECT * FROM btest");
	if(rs) {
		for(const auto &row : rs->Rows()) {
			std::string v = row.at("test_value").value;
			printf("Retrieved: %d bytes from blob.\n", v.length());
		}	
	}

	getchar();
	return 0;
}
	