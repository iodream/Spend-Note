list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetIncomesModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetIncomesModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
