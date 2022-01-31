list(APPEND Spend-Note-Server_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/GetIncomesHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GetIncomesHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeHandler.h
)

add_subdirectory(DTO)
add_subdirectory(ParsersAndFormatters)
add_subdirectory(Utils)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
