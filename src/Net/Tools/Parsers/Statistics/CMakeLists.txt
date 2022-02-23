list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerDayJSONParserBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePercentagePerCategoryJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePercentagePerCategoryJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerCategoryJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerCategoryJSONParser.cpp
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
