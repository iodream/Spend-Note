list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SignupModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SignupModel.cpp
)

add_subdirectory(List)
add_subdirectory(Income)
add_subdirectory(Product)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
