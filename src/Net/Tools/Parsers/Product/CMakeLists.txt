list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductsJSONParser.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
