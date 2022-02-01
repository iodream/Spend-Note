list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONParser.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
