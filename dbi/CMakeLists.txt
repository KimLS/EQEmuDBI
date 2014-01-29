CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(dbi_sources
	dbh.cpp
    dbi.cpp
)

SET(dbi_headers
	any.h
	dbh.h
    dbi.h
)

IF(MySQL_FOUND)
	SET(dbi_sources
		${dbi_sources} dbh-mysql.cpp
	)
	
	SET(dbi_headers
		${dbi_headers} dbh-mysql.h
	)
	INCLUDE_DIRECTORIES("${MySQL_INCLUDE_DIR}")
ENDIF(MySQL_FOUND)

ADD_LIBRARY(dbi ${dbi_sources} ${dbi_headers})

IF(MySQL_FOUND)
	ADD_DEFINITIONS(-DMYSQL_ENGINE)
ENDIF(MySQL_FOUND)

IF(UNIX)
    ADD_DEFINITIONS(-fPIC)
ENDIF(UNIX)

SET(LIBRARY_OUTPUT_PATH ../bin)
