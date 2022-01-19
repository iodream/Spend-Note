list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ListSubPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListSubPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListSubPage.ui
)

add_subdirectory(ListItem)
add_subdirectory(ProductPage)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
