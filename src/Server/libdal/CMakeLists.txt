cmake_minimum_required(VERSION 3.14)

project(DAL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(libdal STATIC
  idbfacade.h
  dbfacade.h
  dbfacade.cpp
  Types.h
  DTOs/User.h
  Repositories/userrepository.h Repositories/userrepository.cpp
)
target_link_libraries(libdal Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(libdal -lpqxx -lpq)
