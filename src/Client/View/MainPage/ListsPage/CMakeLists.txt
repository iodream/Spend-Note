list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsItem.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsPage.ui
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
