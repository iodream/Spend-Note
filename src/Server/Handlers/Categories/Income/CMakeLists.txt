list(APPEND Spend-Note-Server_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeCategoryHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeCategoryHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
