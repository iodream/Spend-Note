list(APPEND Tests_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONFormatterTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONParserTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesJSONFormatterTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesJSONParserTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONFormatterTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONParserTests.cpp
    )

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
