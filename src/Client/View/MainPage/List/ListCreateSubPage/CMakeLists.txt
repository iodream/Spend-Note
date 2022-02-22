list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ListCreateSubPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListCreateSubPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListCreateSubPage.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/Item.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Item.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Item.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductQuickCreateSubPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductQuickCreateSubPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductQuickCreateSubPage.ui)


set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
