list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Logger/ScopedLogger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Logger/ScopedLogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Logger/ScopedLogger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Logger/ScopedLogger.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
