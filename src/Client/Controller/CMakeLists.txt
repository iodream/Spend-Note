list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPClient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/NavHistory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NavHistory.h
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
