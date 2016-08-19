///*
//	Copyright(C) 2014 EQEmu
//	
//	This program is free software; you can redistribute it and/or
//	modify it under the terms of the GNU General Public License
//	as published by the Free Software Foundation; either version 2
//	of the License, or (at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//	
//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//*/
//#ifndef DBI__RS_MYSQL_H
//#define DBI__RS_MYSQL_H
//
//#include "rs.h"
//
//namespace DBI
//{
//
//class MySQLResultSet : public ResultSet
//{
//public:
//	MySQLResultSet(std::vector<std::string> n_fields, std::list<Row> n_rows,
//		unsigned long n_affected_rows, unsigned long n_last_insert_id) 
//	{
//		fields = n_fields;
//		rows = n_rows;
//		affected_rows = n_affected_rows;
//		last_insert_id = n_last_insert_id;
//	}
//	virtual ~MySQLResultSet() { }
//	
//	unsigned long LastInsertId() const { return last_insert_id; }
//private:
//	unsigned long last_insert_id;
//};
//
//}
//
//#endif
//