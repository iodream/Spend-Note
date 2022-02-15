list(APPEND Tests_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/AddListHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateListHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveListHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetListsHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetListStatesHandlerTests.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
