list(APPEND Spend-Note-Server_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/GetListsHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GetListsHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveListHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveListHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/UpdateListHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/UpdateListHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
