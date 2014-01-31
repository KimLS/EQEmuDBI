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

	ResultSet()
	{
	}

	ResultSet(std::vector<std::string> n_fields, std::list<Row> n_rows) 
	{
		fields = n_fields;
		rows = n_rows;
	}
	virtual ~ResultSet() { }
	
	const std::vector<std::string>& Fields() const { return fields; }
	const std::string FieldByID(unsigned int id) { return fields[id]; }
	const std::list<Row>& Rows() const { return rows; }
	size_t RowCount() const { return rows.size(); }
protected:
	std::vector<std::string> fields;
	std::list<Row> rows;
};

}

#endif
