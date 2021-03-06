CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(postgresql_test_sources
	main.cpp
)

SET(postgresql_test_headers
	
)

ADD_EXECUTABLE(postgresql_test ${postgresql_test_sources} ${postgresql_test_headers})

INSTALL(TARGETS postgresql_test RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

TARGET_LINK_LIBRARIES(postgresql_test ${DBI_LIBRARIES})

IF(MSVC)
	SET_TARGET_PROPERTIES(postgresql_test PROPERTIES LINK_FLAGS_RELEASE "/OPT:REF /OPT:ICF")
	TARGET_LINK_LIBRARIES(postgresql_test "Ws2_32.lib")
ENDIF(MSVC)

IF(MINGW)
	TARGET_LINK_LIBRARIES(postgresql_test "WS2_32")
ENDIF(MINGW)

IF(UNIX)
	TARGET_LINK_LIBRARIES(postgresql_test "${CMAKE_DL_LIBS}")
	TARGET_LINK_LIBRARIES(postgresql_test "z")
	TARGET_LINK_LIBRARIES(postgresql_test "m")
	TARGET_LINK_LIBRARIES(postgresql_test "rt")
	TARGET_LINK_LIBRARIES(postgresql_test "pthread")
	ADD_DEFINITIONS(-fPIC)
ENDIF(UNIX)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
