list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensesPerCategoryFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensesPerCategoryFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensesPercentagePerCategoryFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensesPercentagePerCategoryFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensesPerDayFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensesPerDayFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesPerCategoryFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesPerCategoryFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesPercentagePerCategoryFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesPercentagePerCategoryFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesPerDayFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesPerDayFormatter.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
