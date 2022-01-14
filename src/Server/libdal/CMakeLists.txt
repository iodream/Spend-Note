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
	Types.h

	Facade/IDbFacade.h
	Facade/DbFacade.h
	Facade/DbFacade.cpp

	DTOs/User.h
	DTOs/Product.h

	Exceptions/DatabaseFailure.h Exceptions/DatabaseFailure.cpp

	Repositories/UserRepository/UserRepository.h Repositories/UserRepository/UserRepository.cpp
	Repositories/ProductRepository/ProductRepository.h Repositories/ProductRepository/ProductRepository.cpp
)
target_link_libraries(libdal Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(libdal -lpqxx -lpq)
