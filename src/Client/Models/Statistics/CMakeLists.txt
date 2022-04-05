list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerCategoryModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerCategoryModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPercentagePerCategoryModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPercentagePerCategoryModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerDayModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetExpensesPerDayModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
