#ifndef DBI__RS_MYSQL_H
#define DBI__RS_MYSQL_H

#include "rs.h"

namespace DBI
{

class DBI_EXPORT MySQLResultSet : public ResultSet
{
public:
	MySQLResultSet() : affected_rows(0), num_rows(0), last_insert_id(0) { }
	virtual ~MySQLResultSet() { }
	
	virtual const std::vector<std::string>& Fields() const { return fields; }
	virtual const std::List<Row>& Rows() const { return rows; }
	virtual unsigned long AffectedRows() const { return affected_rows; }
	virtual unsigned long RowCount() const { return num_rows; }
	virtual unsigned long LastInsertId() const { return last_insert_id; }
private:
	std::vector<std::string> fields;
	std::list<Row> rows;
	unsigned long affected_rows;
	unsigned long num_rows;
	unsigned long last_insert_id;
};

}

#endif
