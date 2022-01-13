cmake_minimum_required(VERSION 3.5)

project(Spend-Note-Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


set(Spend-Note-Client_SOURCES
    main.cpp
)

add_subdirectory(Controller)
add_subdirectory(DTO)
add_subdirectory(Models)
add_subdirectory(View)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(
        Spend-Note-Client
        MANUAL_FINALIZATION
	${Spend-Note-Client_SOURCES}
    )
endif()


target_include_directories(Spend-Note-Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(Spend-Note-Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Spend-Note-Client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Spend-Note-Client)
endif()
