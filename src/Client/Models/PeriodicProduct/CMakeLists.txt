list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/RemovePeriodicProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemovePeriodicProductModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdatePeriodicProductModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdatePeriodicProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddPeriodicProductModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddPeriodicProductModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetPeriodicProductsModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetPeriodicProductsModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)

