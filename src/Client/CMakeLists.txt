cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Spend-Note-Client VERSION 0.1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core REQUIRED)

list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPClient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Test.cpp
)

list(APPEND Spend-Note-Client_LIBS
    PocoNet
    PocoUtil
    PocoFoundation
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Net ${CMAKE_CURRENT_BINARY_DIR}/Net)

list(APPEND Spend-Note-Client_SOURCES
    ${Spend-Note-Net_SOURCES}
)

add_executable(Spend-Note-Client ${Spend-Note-Client_SOURCES})

target_include_directories(Spend-Note-Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(Spend-Note-Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND Spend-Note-Client_LIBS
    Qt::Core
)

target_link_libraries(
    Spend-Note-Client
    PUBLIC
    ${Spend-Note-Client_LIBS}
)
