list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
