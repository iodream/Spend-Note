list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetIncomesModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetIncomesModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
