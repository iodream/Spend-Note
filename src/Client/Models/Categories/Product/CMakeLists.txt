list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductCategoryModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductCategoryModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductCategoryModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductCategoryModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductCategoryModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductCategoryModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductCategoriesModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductCategoriesModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
