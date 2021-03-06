cmake_minimum_required(VERSION 3.16)

project(Spend-Note-Client VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Charts REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Charts REQUIRED)
find_package(Qt6LinguistTools)


set(Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)


list(APPEND Spend-Note-Client_LIBS
    PocoNet
    PocoUtil
    PocoFoundation
)

add_subdirectory(Entities)

add_subdirectory(Controller)
add_subdirectory(Models)
add_subdirectory(View)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Net ${CMAKE_CURRENT_BINARY_DIR}/Net)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Logger ${CMAKE_CURRENT_BINARY_DIR}/Logger)

list(APPEND Spend-Note-Client_SOURCES
    ${Spend-Note-Net_SOURCES}
    ${Spend-Note-Logger_SOURCES}
)

qt6_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} en_US.ts uk_UA.ts)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(
        Spend-Note-Client
        MANUAL_FINALIZATION
        ${Spend-Note-Client_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
        "${QM_FILES}")
endif()



list(APPEND Spend-Note-Client_LIBS
    Qt::Core
    Qt::Widgets
)



target_include_directories(Spend-Note-Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(
    Spend-Note-Client
    PUBLIC
    ${Spend-Note-Client_LIBS}
)

target_link_libraries(Spend-Note-Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(Spend-Note-Client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Spend-Note-Client)
endif()
