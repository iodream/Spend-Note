list(APPEND Tests_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerCategoryHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPercentagePerCategoryHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerDayHandlerTests.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
