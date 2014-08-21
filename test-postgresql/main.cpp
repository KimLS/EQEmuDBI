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
#include "../dbi/dbi.h"
#include "../dbi/dbh.h"
#include "../dbi/sth.h"
#include "../dbi/rs.h"

#define PrintErr(x, ...) printf("Error at line %d: " x "\n", __LINE__, ##__VA_ARGS__)

int main() {
	DBI::DatabaseAttributes attr;

	auto dbh = DBI::DatabaseInterface::Instance()->Connect("postgresql", "eqdb", "127.0.0.1", "eqdb", "password", attr);
	if(!dbh) {
		PrintErr("Failure to connect.");
		return 1;
	}

	auto rs = dbh->Do("DROP TABLE IF EXISTS db_test");
	if(!rs) {
		PrintErr("Failure to drop table.");
	}

	rs = dbh->Do("CREATE TABLE db_test ("
		"id bigint,"
		"int_value bigint,"
		"real_value real,"
		"text_value text,"
		"blob_value bytea)");

	if(!rs) {
		PrintErr("Failure to get result from create table. Error: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	if(!dbh->Ping()) {
		PrintErr("Failed to ping.");
		return 1;
	}

	if(!dbh->Begin()) {
		PrintErr("Failed to begin.");
		return 1;
	}

	rs = dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
		1,
		nullptr,
		nullptr,
		nullptr,
		nullptr);

	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to insert value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}
	} else {
		PrintErr("Failure to get result from insert: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	std::string blob_value;
	blob_value.assign("hello\0world\0", 12);
	rs = dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
		2,
		(uint8_t)5,
		(float)125.90,
		std::string("A test value"),
		blob_value);

	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to insert value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}
	} else {
		PrintErr("Failure to get result from insert: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	rs = dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
		3,
		(uint16_t)556,
		(double)125.90,
		nullptr,
		nullptr);

	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to insert value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}
	} else {
		PrintErr("Failure to get result from insert: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	rs = dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
		4,
		(uint32_t)518012,
		nullptr,
		nullptr,
		nullptr);

	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to insert value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}
	} else {
		PrintErr("Failure to get result from insert: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	rs = dbh->Do("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)",
		5,
		(uint64_t)42949672960,
		nullptr,
		nullptr,
		nullptr);

	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to insert value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}
	} else {
		PrintErr("Failure to get result from insert: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	if(!dbh->Commit()) {
		PrintErr("Failed to commit.");
		return 1;
	}

	auto sth = dbh->Prepare("INSERT INTO db_test (id, int_value, real_value, text_value, blob_value) VALUES(?, ?, ?, ?, ?)");
	if(!sth) {
		PrintErr("Failed to create prepared statement.");
		return 1;
	}

	rs = sth->Execute(6, 2134, 125.9, std::string("Test value"), blob_value);
	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to insert value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}
	} else {
		PrintErr("Failure to get result from insert: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	sth = dbh->Prepare("SELECT int_value, real_value, text_value, blob_value FROM db_test WHERE id = ?");
	if(!sth) {
		PrintErr("Failed to create prepared statement.");
		return 1;
	}

	rs = sth->Execute(1);
	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to select value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}

		auto row = (*rs->Rows().begin());
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
	} else {
		PrintErr("Failure to get result from select: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	rs = sth->Execute(2);
	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to select value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}

		auto row = (*rs->Rows().begin());
		if(row["int_value"].is_null) {
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
	} else {
		PrintErr("Failure to get result from select: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	rs = sth->Execute(3);
	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to select value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}

		auto row = (*rs->Rows().begin());
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
	} else {
		PrintErr("Failure to get result from select: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	rs = sth->Execute(4);
	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to select value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}

		auto row = (*rs->Rows().begin());
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
	} else {
		PrintErr("Failure to get result from select: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	rs = sth->Execute(5);
	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to select value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}

		auto row = (*rs->Rows().begin());
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
	} else {
		PrintErr("Failure to get result from select: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	rs = sth->Execute(6);
	if(rs) {
		if(rs->AffectedRows() != 1) {
			PrintErr("Failure to select value: %s", dbh->ErrorMessage().c_str());
			return 1;
		}

		auto row = (*rs->Rows().begin());
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
	} else {
		PrintErr("Failure to get result from select: %s", dbh->ErrorMessage().c_str());
		return 1;
	}

	printf("Tests passed");
	return 0;
}
