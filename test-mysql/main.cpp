/*
	Copyright(C) 2014 EQEmu
	
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <stdio.h>
#include <string.h>
#include "../dbi/dbh-mysql.h"

#define PrintErr(x, ...) printf("Error at line %d: " x "\n", __LINE__, ##__VA_ARGS__)

int main() {
	try {
		auto dbh = new DBI::MySQLDatabaseHandle();
		DBI::DatabaseAttributes attr;
		attr["mysql_reconnect"] = "1";

		dbh->Connect("eqdb", "127.0.0.1", "root", "blink", attr);

		dbh->Do("DROP TABLE IF EXISTS db_test");

		dbh->Do("CREATE TABLE db_test ("
			"id BIGINT,"
			"int_value BIGINT,"
			"real_value DOUBLE,"
			"text_value TEXT,"
			"blob_value BLOB,"
			"PRIMARY KEY(id))");

		dbh->Ping();
		dbh->Begin();

		dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
				1,
				nullptr,
				nullptr,
				nullptr,
				nullptr);

		std::string blob_value;
		blob_value.assign("hello\0world\0", 12);
		dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
			2,
			(uint8_t)5,
			(float)125.90,
			std::string("A test value"),
			blob_value);
		
		dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
			3,
			(uint16_t)556,
			(double)125.90,
			nullptr,
			nullptr);
		
		dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
			4,
			(uint32_t)518012,
			nullptr,
			nullptr,
			nullptr);

		dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
			5,
			(uint64_t)42949672960,
			nullptr,
			nullptr,
			nullptr);

		dbh->Commit();

		auto sth = dbh->Prepare("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)");
		if(!sth) {
			PrintErr("Failed to create prepared statement.");
			return 1;
		}

		auto rs = sth->Execute(6, 2134, 125.9, std::string("Test value"), blob_value);
		if (rs->AffectedRows() != 1) {
			PrintErr("Failure to insert value");
			return 1;
		}

		sth = dbh->Prepare("SELECT int_value, real_value, text_value, blob_value FROM db_test WHERE id = ?");
		rs = sth->Execute(1);

		auto rows = rs->Rows();
		if (rows.size() != 1) {
			PrintErr("Failure to select value, 1 row not returned.");
			return 1;
		}

		auto row = rows.front();

		if(!row["int_value"].is_null) {
			PrintErr("Row int_value was incorrect value in row 1");
			return 1;
		}
		
		if(!row["real_value"].is_null) {
			PrintErr("Row real_value was incorrect value in row 1");
			return 1;
		}
		
		if(!row["text_value"].is_null) {
			PrintErr("Row text_value was incorrect value in row 1");
			return 1;
		}
		
		if(!row["blob_value"].is_null) {
			PrintErr("Row blob_value was incorrect value in row 1");
			return 1;
		}

		rs = sth->Execute(2);
		rows = rs->Rows();

		if (rows.size() != 1) {
			PrintErr("Failure to select value, 1 row not returned.");
			return 1;
		}

		row = rows.front();

		if (row["int_value"].is_null) {
			PrintErr("Row int_value was incorrect value in row 2");
			return 1;
		} else {
			uint64_t val = std::stoll(row["int_value"].value);
			if(val != 5) {
				PrintErr("Row int_value was incorrect value in row 2");
				return 1;
			}
		}
		
		if(row["real_value"].is_null) {
			PrintErr("Row real_value was incorrect value in row 2");
			return 1;
		} else {
			double val = std::stod(row["real_value"].value);
			if(val > 126.0 || val < 125.8) {
				PrintErr("Row real_value was incorrect value in row 2");
				return 1;
			}
		}
		
		if(row["text_value"].is_null) {
			PrintErr("Row text_value was incorrect value in row 2");
			return 1;
		} else {
			if(row["text_value"].value.compare("A test value") != 0) {
				PrintErr("Row text_value was incorrect value in row 2");
				return 1;
			}
		}
		
		if(row["blob_value"].is_null) {
			PrintErr("Row blob_value was incorrect value in row 2");
			return 1;
		} else {
			if(row["blob_value"].value.length() != 12) {
				PrintErr("Row blob_value was incorrect length in row 2");
				return 1;
			}
		
			if(memcmp(row["blob_value"].value.c_str(), "hello\0world\0", 12) != 0) {
				PrintErr("Row blob_value was incorrect value in row 2");
				return 1;
			}
		}

		rs = sth->Execute(3);
		rows = rs->Rows();

		if (rows.size() != 1) {
			PrintErr("Failure to select value, 1 row not returned.");
			return 1;
		}

		row = rows.front();

		if(row["int_value"].is_null) {
			PrintErr("Row int_value was incorrect value in row 3");
			return 1;
		} else {
			uint64_t val = std::stoll(row["int_value"].value);
			if(val != 556) {
				PrintErr("Row int_value was incorrect value in row 3");
				return 1;
			}
		}
		
		if(row["real_value"].is_null) {
			PrintErr("Row real_value was incorrect value in row 3");
			return 1;
		} else {
			double val = std::stod(row["real_value"].value);
			if(val > 126.0 || val < 125.8) {
				PrintErr("Row real_value was incorrect value in row 3");
				return 1;
			}
		}
		
		if(!row["text_value"].is_null) {
			PrintErr("Row text_value was incorrect value in row 3");
			return 1;
		}
		
		if(!row["blob_value"].is_null) {
			PrintErr("Row blob_value was incorrect value in row 3");
			return 1;
		}

		rs = sth->Execute(4);
		rows = rs->Rows();

		if (rows.size() != 1) {
			PrintErr("Failure to select value, 1 row not returned.");
			return 1;
		}

		row = rows.front();

		if(row["int_value"].is_null) {
			PrintErr("Row int_value was incorrect value in row 4");
			return 1;
		} else {
			uint64_t val = std::stoll(row["int_value"].value);
			if(val != 518012) {
				PrintErr("Row int_value was incorrect value in row 4");
				return 1;
			}
		}
		
		if(!row["real_value"].is_null) {
			PrintErr("Row real_value was incorrect value in row 4");
			return 1;
		}
		
		if(!row["text_value"].is_null) {
			PrintErr("Row text_value was incorrect value in row 4");
			return 1;
		}
		
		if(!row["blob_value"].is_null) {
			PrintErr("Row blob_value was incorrect value in row 4");
			return 1;
		}

		rs = sth->Execute(5);
		rows = rs->Rows();

		if (rows.size() != 1) {
			PrintErr("Failure to select value, 1 row not returned.");
			return 1;
		}

		row = rows.front();

		if(row["int_value"].is_null) {
			PrintErr("Row int_value was incorrect value in row 5");
			return 1;
		} else {
			uint64_t val = std::stoll(row["int_value"].value);
			if(val != 42949672960) {
				PrintErr("Row int_value was incorrect value in row 5");
				return 1;
			}
		}
		
		if(!row["real_value"].is_null) {
			PrintErr("Row real_value was incorrect value in row 5");
			return 1;
		}
		
		if(!row["text_value"].is_null) {
			PrintErr("Row text_value was incorrect value in row 5");
			return 1;
		}
		
		if(!row["blob_value"].is_null) {
			PrintErr("Row blob_value was incorrect value in row 5");
			return 1;
		}

		rs = sth->Execute(6);
		rows = rs->Rows();

		if (rows.size() != 1) {
			PrintErr("Failure to select value, 1 row not returned.");
			return 1;
		}

		row = rows.front();

		if(row["int_value"].is_null) {
			PrintErr("Row int_value was incorrect value in row 6");
			return 1;
		} else {
			uint64_t val = std::stoll(row["int_value"].value);
			if(val != 2134) {
				PrintErr("Row int_value was incorrect value in row 6");
				return 1;
			}
		}
		
		if(row["real_value"].is_null) {
			PrintErr("Row real_value was incorrect value in row 6");
			return 1;
		} else {
			double val = std::stod(row["real_value"].value);
			if(val > 126.0 || val < 125.8) {
				PrintErr("Row real_value was incorrect value in row 6");
				return 1;
			}
		}
		
		if(row["text_value"].is_null) {
			PrintErr("Row text_value was incorrect value in row 6");
			return 1;
		} else {
			if(row["text_value"].value.compare("Test value") != 0) {
				PrintErr("Row text_value was incorrect value in row 6");
				return 1;
			}
		}
		
		if(row["blob_value"].is_null) {
			PrintErr("Row blob_value was incorrect value in row 6");
			return 1;
		} else {
			if(row["blob_value"].value.length() != 12) {
				PrintErr("Row blob_value was incorrect length in row 6");
				return 1;
			}
		
			if(memcmp(row["blob_value"].value.c_str(), "hello\0world\0", 12) != 0) {
				PrintErr("Row blob_value was incorrect value in row 6");
				return 1;
			}
		}
	}
	catch (std::exception &ex) {
		printf("Tests failed with message: %s", ex.what());
		return 1;
	}
	
	printf("Tests passed");
	return 0;
}
