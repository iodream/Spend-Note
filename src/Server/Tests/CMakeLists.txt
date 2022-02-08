list(APPEND Tests_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/MockDbFacade.h
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GetProductsHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GetListsHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/AddProductHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GetIncomesHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SignupTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LoginTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ListJSONFormatterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ListJSONParserTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ListsJSONFormatterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ListsJSONParserTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ListIdJSONFormatterTest.cpp
	#${CMAKE_CURRENT_SOURCE_DIR}/ListIdJSONParserTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONFormatterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONParserTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductsJSONFormatterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductsJSONParserTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONFormatterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONParserTest.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
