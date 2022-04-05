list(APPEND Tests_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONFormatterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONParserTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerCategoryJSONFormatterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerCategoryJSONParserTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePercentagePerCategoryJSONFormatterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePercentagePerCategoryJSONParserTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerDayJSONFormatterTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerDayJSONParserTest.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
