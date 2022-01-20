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

option(TestLibdal "build test executable" ON)

add_library(libdal STATIC
  Types.h

  DTOs/Income.h
  DTOs/List.h
  DTOs/User.h
  DTOs/IncomeCategory.h
  DTOs/ListState.h

  Repositories/IncomeRepository/IncomeRepository.h Repositories/IncomeRepository/IncomeRepository.cpp
  Repositories/ListRepository/ListRepository.h Repositories/ListRepository/ListRepository.cpp
  Repositories/UserRepository/UserRepository.h Repositories/UserRepository/UserRepository.cpp
  Repositories/IncomeCategoryRepository/IncomeCategoryRepository.h Repositories/IncomeCategoryRepository/IncomeCategoryRepository.cpp
  Repositories/ListStateRepository/ListStateRepository.h Repositories/ListStateRepository/ListStateRepository.cpp

  Exceptions/databasefailure.h  Exceptions/databasefailure.cpp

  Facade/idbfacade.h
  Facade/dbfacade.h Facade/dbfacade.cpp
)
target_link_libraries(libdal Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(libdal -lpqxx -lpq)
if(TestLibdal)
    add_executable(TestLibdal main.cpp)
    target_link_libraries(TestLibdal libdal)
endif()
