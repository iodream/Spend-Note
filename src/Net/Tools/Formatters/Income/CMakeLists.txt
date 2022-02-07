list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONFormatterBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoryJSONFormatterBase.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
