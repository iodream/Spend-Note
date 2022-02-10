list(APPEND Tests_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/AddIncomeHandlerTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GetIncomesHandlerTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RemoveIncomeHandlerTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UpdateIncomeHandlerTests.cpp
)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
