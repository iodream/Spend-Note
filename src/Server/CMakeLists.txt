add_subdirectory(Handlers)

list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HandlerFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HandlerFactory.h
)

list(APPEND Spend-Note-Server_LIBS
    PocoNet
    PocoUtil
    PocoFoundation
    PocoJWT
    PocoJSON
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Net ${CMAKE_CURRENT_BINARY_DIR}/Net)

list(APPEND Spend-Note-Server_SOURCES
    ${Spend-Note-Net_SOURCES}
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
set(Spend-Note-Server_LIBS "${Spend-Note-Server_LIBS}" PARENT_SCOPE)
