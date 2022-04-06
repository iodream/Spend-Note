list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Balance.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPerCategory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPercentagePerCategory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticPerDayBase.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
