list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/EchoHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FakeLoginHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FakeGetListsHandler.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
