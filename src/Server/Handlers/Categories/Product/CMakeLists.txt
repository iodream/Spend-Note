list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductCategoriesHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductCategoriesHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductCategoryHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductCategoryHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductCategoryHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductCategoryHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductCategoryHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductCategoryHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
