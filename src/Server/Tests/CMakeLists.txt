list(APPEND Tests_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/MockDbFacade.h
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SignupTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LoginTests.cpp
)

add_subdirectory(Entities)
add_subdirectory(Handlers)

set(Tests_SOURCES "${Tests_SOURCES}" PARENT_SCOPE)
