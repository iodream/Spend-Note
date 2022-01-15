add_subdirectory(Handlers)

list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HandlerFactory.cpp
)

list(APPEND Spend-Note-Server_LIBS
    PocoNet
    PocoUtil
    PocoFoundation
    PocoJWT
    PocoJSON
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
set(Spend-Note-Server_LIBS "${Spend-Note-Server_LIBS}" PARENT_SCOPE)
