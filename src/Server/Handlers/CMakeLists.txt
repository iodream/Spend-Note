list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FakeLoginHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FakeLoginHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ICommandHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/EchoHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EchoHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AuthorizedHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AuthorizedHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FakeGetListsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FakeGetListsHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetListsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetListsHandler.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
