list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryJSONFormatterBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryIdJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryIdJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONFormatterBase.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
