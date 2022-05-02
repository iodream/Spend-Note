list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetPeriodicProductsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetPeriodicProductsHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddPeriodicProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddPeriodicProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdatePeriodicProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdatePeriodicProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemovePeriodicProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemovePeriodicProductHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
