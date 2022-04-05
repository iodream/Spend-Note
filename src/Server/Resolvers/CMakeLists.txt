list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/RootResolver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RootResolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductsResolver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductsResolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoriesResolver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoriesResolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UsersResolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UsersResolver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsResolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ListsResolver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesResolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomesResolver.h
	${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoriesResolver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoriesResolver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

add_subdirectory(ParametersParsers)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
