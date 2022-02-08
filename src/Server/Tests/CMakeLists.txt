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
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONFormatterTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONParserTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomesJSONFormatterTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomesJSONParserTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONFormatterTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONParserTests.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
