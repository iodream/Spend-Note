list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPerDayJSONFormatterBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPercentagePerCategoryJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPercentagePerCategoryJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPerCategoryJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPerCategoryJSONFormatter.cpp
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
