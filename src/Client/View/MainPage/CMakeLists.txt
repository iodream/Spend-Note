list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.ui
)

add_subdirectory(ListSubPage)
add_subdirectory(IncomesSubPage)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
