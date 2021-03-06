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

option(TestLibdal "build test executable" OFF)

add_library(libdal STATIC
	Types.h

	DTOs/Income.h
	DTOs/List.h
	DTOs/IncomeCategory.h
	DTOs/ListState.h
	DTOs/User.h
	DTOs/Product.h
	DTOs/Statistics.h
	DTOs/ProductCategory.h
	DTOs/VerificationCode.h
	DTOs/PeriodicProduct.h
	DTOs/PeriodicIncome.h
	DTOs/PeriodType.h

	Repositories/IncomeRepository/IncomeRepository.h Repositories/IncomeRepository/IncomeRepository.cpp
	Repositories/ListRepository/ListRepository.h Repositories/ListRepository/ListRepository.cpp
	Repositories/IncomeCategoryRepository/IncomeCategoryRepository.h Repositories/IncomeCategoryRepository/IncomeCategoryRepository.cpp
	Repositories/ListStateRepository/ListStateRepository.h Repositories/ListStateRepository/ListStateRepository.cpp
	Repositories/UserRepository/UserRepository.h Repositories/UserRepository/UserRepository.cpp
	Repositories/ProductRepository/ProductRepository.h Repositories/ProductRepository/ProductRepository.cpp
	Repositories/ProductCategoryRepository/ProductCategoryRepository.h Repositories/ProductCategoryRepository/ProductCategoryRepository.cpp
	Repositories/BalanceRepository/BalanceRepository.h Repositories/BalanceRepository/BalanceRepository.cpp
	Repositories/StatisticsRepository/StatisticsRepository.h Repositories/StatisticsRepository/StatisticsRepository.cpp
	Repositories/VerificationCodeRepository/VerificationCodeRepository.h Repositories/VerificationCodeRepository/VerificationCodeRepository.cpp
	Repositories/RecommendationRepository/RecommendationRepository.h Repositories/RecommendationRepository/RecommendationRepository.cpp
	Repositories/PeriodicProductRepository/PeriodicProductRepository.h Repositories/PeriodicProductRepository/PeriodicProductRepository.cpp
	Repositories/PeriodicIncomeRepository/PeriodicIncomeRepository.h Repositories/PeriodicIncomeRepository/PeriodicIncomeRepository.cpp

	Facade/IDbFacade.h
	Facade/DbFacade.h
	Facade/DbFacade.cpp

	Exceptions/DatabaseFailure.h
	Exceptions/SQLFailure.h
	Exceptions/NonexistentResource.h

	DatabaseNames.h
)
target_link_libraries(libdal Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(libdal -lpqxx -lpq)

if(TestLibdal)
	add_executable(TestLibdal main.cpp)
	target_link_libraries(TestLibdal libdal)
endif()
