#ifndef DBI__RS_MYSQL_H
#define DBI__RS_MYSQL_H

#include "rs.h"

namespace DBI
{

class MySQLResultSet : public ResultSet
{
public:
	MySQLResultSet(std::vector<std::string> n_fields, std::list<Row> n_rows,
		unsigned long n_affected_rows, unsigned long n_last_insert_id) 
	{
		fields = n_fields;
		rows = n_rows;
		affected_rows = n_affected_rows;
		last_insert_id = n_last_insert_id;
	}
	virtual ~MySQLResultSet() { }
	
	unsigned long LastInsertId() const { return last_insert_id; }
private:
	unsigned long last_insert_id;
};

}

#endif
