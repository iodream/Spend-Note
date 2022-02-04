list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryJSONParserBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONParserBase.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
