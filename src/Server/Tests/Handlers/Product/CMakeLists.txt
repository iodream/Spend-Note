list(APPEND Tests_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/AddProductHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductsHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetProductCategoriesHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UpdateProductHandlerTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveProductHandlerTests.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
