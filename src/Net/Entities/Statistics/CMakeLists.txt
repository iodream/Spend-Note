list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Balance.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerCategory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePercentagePerCategory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpensePerDayBase.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
