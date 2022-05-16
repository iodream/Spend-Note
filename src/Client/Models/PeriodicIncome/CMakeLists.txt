list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/RemovePeriodicIncomeModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemovePeriodicIncomeModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetPeriodicIncomesModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetPeriodicIncomesModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddPeriodicIncomeModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddPeriodicIncomeModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdatePeriodicIncomeModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdatePeriodicIncomeModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
