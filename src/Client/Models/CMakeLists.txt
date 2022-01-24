list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginModel.cpp
)

add_subdirectory(List)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
