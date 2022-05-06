list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SignupModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SignupModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CheckVerificationModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CheckVerificationModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddVerificationModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddVerificationModel.cpp
)

add_subdirectory(List)
add_subdirectory(Income)
add_subdirectory(Product)
add_subdirectory(Statistics)
add_subdirectory(Categories)
add_subdirectory(User)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
