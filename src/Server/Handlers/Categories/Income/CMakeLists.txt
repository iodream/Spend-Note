list(APPEND Spend-Note-Server_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeCategoryHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeCategoryHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeCategoryHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeCategoryHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeCategoryHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeCategoryHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/GetIncomeCategoriesHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GetIncomeCategoriesHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
	${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
