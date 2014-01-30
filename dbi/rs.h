#ifndef DBI__RS_H
#define DBI__RS_H

#include "dbi.h"

namespace DBI
{

class ResultSet
{
public:
	struct FieldData
	{
		FieldData() 
		: is_null(false), error(false) { }
		FieldData(bool is_null_, bool error_, std::string value_)
		: is_null(is_null_), error(error_), value(value_) { }
		bool is_null;
		bool error;
		std::string value;
	};

	typedef std::map<std::string, FieldData> Row;

	ResultSet(std::vector<std::string> n_fields, std::list<Row> n_rows,
		unsigned long n_affected_rows, unsigned long n_num_rows, unsigned long n_last_insert_id) 
	{
		fields = n_fields;
		rows = n_rows;
		affected_rows = n_affected_rows;
		num_rows = n_num_rows;
		last_insert_id = n_last_insert_id;
	}
	virtual ~ResultSet() { }
	
	virtual const std::vector<std::string>& Fields() const { return fields; }
	virtual const std::list<Row>& Rows() const { return rows; }
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
