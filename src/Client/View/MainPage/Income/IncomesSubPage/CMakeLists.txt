list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeListItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeListItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeListItem.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeListSubPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeListSubPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeListSubPage.ui
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
