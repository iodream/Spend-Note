list(APPEND Spend-Note-Client_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/GetListsModel.h
	${CMAKE_CURRENT_SOURCE_DIR}/GetListsModel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/AddNewListModel.h
	${CMAKE_CURRENT_SOURCE_DIR}/AddNewListModel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveListModel.h
	${CMAKE_CURRENT_SOURCE_DIR}/RemoveListModel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UpdateListModel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/UpdateListModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
