list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPClient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginPageController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LoginPageController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SignupPageController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SignupPageController.h
)

add_subdirectory(MainPage)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
