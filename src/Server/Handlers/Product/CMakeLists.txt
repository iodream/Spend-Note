list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetRecommendationProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetRecommendationProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsForPeriodicProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsForPeriodicProductHandler.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
