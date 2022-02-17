list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ListJSONParserBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListIdJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListIdJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListStateJSONParserBase.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
