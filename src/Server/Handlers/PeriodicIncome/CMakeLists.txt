list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetPeriodicIncomesHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetPeriodicIncomesHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddPeriodicIncomeHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddPeriodicIncomeHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdatePeriodicIncomeHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdatePeriodicIncomeHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemovePeriodicIncomeHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemovePeriodicIncomeHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
