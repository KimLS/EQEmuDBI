#ifndef DBI__RS_H
#define DBI__RS_H

#include "dbi.h"

namespace DBI
{

class ResultSet
{
public:
	typedef std::map<std::string, std::pair<bool, std::string>> Row;
	typedef std::vector<std::pair<bool, std::string>> RowIdx;

	ResultSet(std::vector<std::string> n_fields, std::list<Row> n_rows, std::list<RowIdx> n_rows_idx,
		unsigned long n_affected_rows, unsigned long n_num_rows, unsigned long n_last_insert_id) 
	{
		fields = n_fields;
		rows = n_rows;
		rows_idx = n_rows_idx;
		affected_rows = n_affected_rows;
		num_rows = n_num_rows;
		last_insert_id = n_last_insert_id;
	}
	virtual ~ResultSet() { }
	
	virtual const std::vector<std::string>& Fields() const { return fields; }
	virtual const std::list<Row>& Rows() const { return rows; }
	virtual const std::list<RowIdx>& RowsByIndex() const { return rows_idx; }
	virtual unsigned long AffectedRows() const { return affected_rows; }
	virtual unsigned long RowCount() const { return num_rows; }
	virtual unsigned long LastInsertId() const { return last_insert_id; }
private:
	std::vector<std::string> fields;
	std::list<Row> rows;
	std::list<RowIdx> rows_idx;
	unsigned long affected_rows;
	unsigned long num_rows;
	unsigned long last_insert_id;
};

}

#endif
