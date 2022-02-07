list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
