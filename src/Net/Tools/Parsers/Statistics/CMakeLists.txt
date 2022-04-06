list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BalanceJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPerDayJSONParserBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPercentagePerCategoryJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPercentagePerCategoryJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPerCategoryJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPerCategoryJSONParser.cpp
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
