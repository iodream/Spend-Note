list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ListItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListItem.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsSubPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsSubPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsSubPage.ui
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
