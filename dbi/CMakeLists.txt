CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(dbi_sources
)

SET(dbi_headers
	dbh.h
	rs.h
	sth.h
)

SET(dbi_sources
	${dbi_sources} sqlite3.c dbh-sqlite.cpp sth-sqlite.cpp
)
	
SET(dbi_headers
	${dbi_headers} dbh-sqlite.h sth-sqlite.h
)

IF(MySQL_FOUND)
	SET(dbi_sources
		${dbi_sources} dbh-mysql.cpp sth-mysql.cpp
	)
	
	SET(dbi_headers
		${dbi_headers} dbh-mysql.h sth-mysql.h
	)
	INCLUDE_DIRECTORIES("${MySQL_INCLUDE_DIR}")
ENDIF(MySQL_FOUND)

IF(PostgreSQL_FOUND)
	SET(dbi_sources
		${dbi_sources} dbh-pg.cpp sth-pg.cpp
	)
	
	SET(dbi_headers
		${dbi_headers} dbh-pg.h sth-pg.h
	)
	INCLUDE_DIRECTORIES("${PostgreSQL_INCLUDE_DIRS}")
ENDIF(PostgreSQL_FOUND)

ADD_LIBRARY(dbi ${dbi_sources} ${dbi_headers})

IF(MySQL_FOUND)
	ADD_DEFINITIONS(-DMYSQL_ENGINE)
ENDIF(MySQL_FOUND)

IF(PostgreSQL_FOUND)
	ADD_DEFINITIONS(-DPOSTGRESQL_ENGINE)
ENDIF(PostgreSQL_FOUND)

ADD_DEFINITIONS(-DSQLITE_ENGINE)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
