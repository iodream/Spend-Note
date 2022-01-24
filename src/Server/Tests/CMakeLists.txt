list(APPEND Tests_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MockDbFacade.h
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductHandler.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
