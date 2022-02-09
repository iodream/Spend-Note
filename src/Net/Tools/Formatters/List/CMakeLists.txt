list(APPEND Spend-Note-Net_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/ListJSONFormatterBase.h
	${CMAKE_CURRENT_SOURCE_DIR}/ListIdJSONFormatter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ListIdJSONFormatter.h
	${CMAKE_CURRENT_SOURCE_DIR}/ListStateJSONFormatterBase.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
