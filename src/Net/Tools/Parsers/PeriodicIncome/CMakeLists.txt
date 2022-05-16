list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/PeriodicIncomeIdJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PeriodicIncomeIdJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PeriodicIncomeJSONParserBase.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
