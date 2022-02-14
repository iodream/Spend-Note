list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ICommandHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AuthorizedHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AuthorizedHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SignupHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SignupHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MethodNotAllowedHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MethodNotAllowedHandler.h
)

add_subdirectory(Entities)

add_subdirectory(Product)
add_subdirectory(List)
add_subdirectory(Income)
add_subdirectory(Statistics)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
