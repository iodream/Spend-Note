list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerCategoryHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerCategoryHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPercentagePerCategoryHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPercentagePerCategoryHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerDayHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerDayHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

add_subdirectory(StatisticsFormatters)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
