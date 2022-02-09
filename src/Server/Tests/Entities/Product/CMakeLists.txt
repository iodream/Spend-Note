list(APPEND Tests_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONFormatterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONParserTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductsJSONFormatterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductsJSONParserTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONFormatterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONParserTest.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
