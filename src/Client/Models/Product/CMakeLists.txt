list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsForPeriodicProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsForPeriodicProductModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetRecommendationProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetRecommendationProductModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
