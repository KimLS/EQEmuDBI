#include <stdio.h>
#include "../dbi/dbi.h"
#include "../dbi/dbh.h"
#include "../dbi/sth.h"
#include "../dbi/rs.h"
#include "../dbi/sqlite3.h"

int main() {
	DBI::DatabaseAttributes attr;
	
	auto dbh = DBI::DatabaseInterface::Instance()->Connect("sqlite", "test.db", "", "", "", attr);
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

	getchar();
	return 0;
}
