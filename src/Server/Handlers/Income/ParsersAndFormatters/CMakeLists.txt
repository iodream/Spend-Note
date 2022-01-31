list(APPEND Spend-Note-Server_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONParser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONFormatter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONParser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONFormatter.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
