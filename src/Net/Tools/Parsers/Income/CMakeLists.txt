list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoryJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesJSONParser.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
