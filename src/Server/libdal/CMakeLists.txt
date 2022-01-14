cmake_minimum_required(VERSION 3.14)

project(dal LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(dal
  main.cpp
  Types.h
  DTOs/Income.h
  DTOs/List.h
  DTOs/User.h
  Repositories/IncomeRepository/IncomeRepository.h Repositories/IncomeRepository/IncomeRepository.cpp
  Repositories/ListRepository/ListRepository.h Repositories/ListRepository/ListRepository.cpp
  Repositories/UserRepository/UserRepository.h Repositories/UserRepository/UserRepository.cpp

  Exceptions/databasefailure.h  Exceptions/databasefailure.cpp

  Fasade/idbfacade.h
  Fasade/dbfacade.h Fasade/dbfacade.cpp
  )

target_link_libraries(dal Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(dal -lpqxx -lpq)





