list(APPEND Spend-Note-Server_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Common.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Common.h
	${CMAKE_CURRENT_SOURCE_DIR}/LoginHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LoginHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/ICommandHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/EchoHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EchoHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/AuthorizedHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/AuthorizedHandler.h
	${CMAKE_CURRENT_SOURCE_DIR}/SignupHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SignupHandler.h
)

add_subdirectory(Product)
add_subdirectory(List)
add_subdirectory(Income)
add_subdirectory(Entities)
add_subdirectory(ParsersAndFormatters/Product)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
