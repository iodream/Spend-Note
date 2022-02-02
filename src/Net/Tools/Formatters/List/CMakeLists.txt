list(APPEND Spend-Note-Server_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/ListJSONFormatter.h
	${CMAKE_CURRENT_SOURCE_DIR}/ListIdJSONFormatter.h
	${CMAKE_CURRENT_SOURCE_DIR}/ListStateJSONFormatter.h
	${CMAKE_CURRENT_SOURCE_DIR}/ListVectorJSONFormatter.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
