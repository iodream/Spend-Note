list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginWindow.ui
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
