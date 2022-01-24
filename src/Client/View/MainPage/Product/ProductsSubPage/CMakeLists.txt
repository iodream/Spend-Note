list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductItem.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductsSubPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductsSubPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductsSubPage.ui
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
