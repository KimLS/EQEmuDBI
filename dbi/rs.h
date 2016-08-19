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
#ifndef DBI__RS_H
#define DBI__RS_H

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

	ResultSet() : affected_rows(0)
	{
	}

	ResultSet(std::vector<std::string> n_fields, std::list<Row> n_rows, size_t affected_rows_) 
	{
		fields = n_fields;
		rows = n_rows;
		affected_rows = affected_rows_;
	}
	virtual ~ResultSet() { }
	
	const std::vector<std::string>& Fields() const { return fields; }
	const std::string FieldByID(unsigned int id) { return fields[id]; }
	const std::list<Row>& Rows() const { return rows; }
	size_t RowCount() const { return rows.size(); }
	size_t AffectedRows() const { return affected_rows; }
protected:
	std::vector<std::string> fields;
	std::list<Row> rows;
	size_t affected_rows;
};

}

#endif
