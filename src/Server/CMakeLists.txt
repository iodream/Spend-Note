cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(SpendNoteServer VERSION 0.1)

configure_file(SpendNoteServer_Config.h.in SpendNoteServer_Config.h)

unset(ENABLE_SPEND_NOTE_TESTS CACHE)
option(ENABLE_SPEND_NOTE_TESTS "Enables unit tests building" ON)

find_package(Qt6 COMPONENTS Core REQUIRED)

add_subdirectory(Handlers)

if(ENABLE_SPEND_NOTE_TESTS)
    add_subdirectory(Tests)
endif()

list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Error.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HandlerFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HandlerFactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPRequestHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPRequestHandler.h
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

add_executable(
    Spend-Note-Server
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
    ${Spend-Note-Server_SOURCES})

target_include_directories(Spend-Note-Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(Spend-Note-Server PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(Spend-Note-Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libdal)

if(ENABLE_SPEND_NOTE_TESTS)
    add_executable(
	Spend-Note-Tests
	${Tests_SOURCES}
	${Spend-Note-Server_SOURCES})

    target_include_directories(Spend-Note-Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
    target_include_directories(Spend-Note-Tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_include_directories(Spend-Note-Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libdal)
endif()

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

if(ENABLE_SPEND_NOTE_TESTS)
    target_link_libraries(
	Spend-Note-Tests
	PUBLIC
	${Spend-Note-Server_LIBS}
	gmock
	gtest
    )
endif()
