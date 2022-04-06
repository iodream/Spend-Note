list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsFormatterManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsFormatterManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

add_subdirectory(StatisticsFormatters)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
