list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeJSONParserBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdJSONParser.h
	${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoryJSONParserBase.h
	${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoryIdJSONParser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoryIdJSONParser.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
