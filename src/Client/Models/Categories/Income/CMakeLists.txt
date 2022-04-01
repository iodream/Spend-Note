list(APPEND Spend-Note-Client_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeCategoryModel.h
	${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeCategoryModel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeCategoryModel.h
	${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeCategoryModel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeCategoryModel.h
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeCategoryModel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GetIncomeCategoriesModel.h
	${CMAKE_CURRENT_SOURCE_DIR}/GetIncomeCategoriesModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
