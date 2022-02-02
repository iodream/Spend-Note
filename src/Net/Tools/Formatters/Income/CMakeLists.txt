list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoryJSONFormatter.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
