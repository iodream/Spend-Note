cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(SpendNoteServer VERSION 0.1)

configure_file(SpendNoteServer_Config.h.in SpendNoteServer_Config.h)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core REQUIRED)

add_subdirectory(Handlers)

list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Error.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HandlerFactory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/HandlerFactory.h
)

list(APPEND Spend-Note-Server_LIBS
    PocoNet
    PocoUtil
    PocoFoundation
    PocoJWT
    PocoJSON
)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Net ${CMAKE_CURRENT_BINARY_DIR}/Net)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libdal ${CMAKE_CURRENT_BINARY_DIR}/libdal)


list(APPEND Spend-Note-Server_SOURCES
    ${Spend-Note-Net_SOURCES}
)

add_executable(Spend-Note-Server ${Spend-Note-Server_SOURCES})
target_include_directories(Spend-Note-Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(Spend-Note-Server PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(Spend-Note-Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libdal)

if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(Spend-Note-Server PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

list(APPEND Spend-Note-Server_LIBS
    Qt::Core
    libdal
)
target_link_libraries(
    Spend-Note-Server
    PUBLIC
    ${Spend-Note-Server_LIBS}
)
