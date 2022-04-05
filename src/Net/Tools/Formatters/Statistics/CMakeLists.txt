list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerDayJSONFormatterBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePercentagePerCategoryJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePercentagePerCategoryJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerCategoryJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerCategoryJSONFormatter.cpp
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
