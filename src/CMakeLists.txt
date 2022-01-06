cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Spend-Note VERSION 0.1)

configure_file(Spend-NoteConfig.h.in Spend-NoteConfig.h)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(GTest REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)

add_subdirectory(Server)
add_subdirectory(Client)

add_executable(Spend-Note-Server ${Spend-Note-Server_SOURCES})
target_include_directories(Spend-Note-Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(Spend-Note-Server PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

list(APPEND Spend-Note-Server_LIBS
    Qt::Core
)

target_link_libraries(
    Spend-Note-Server
    PUBLIC
    ${Spend-Note-Server_LIBS}
)

#target_link_libraries(
#    Test
#    PUBLIC
#    ${EXTRA_LIBS}
#    gtest
#    pthread
#)

