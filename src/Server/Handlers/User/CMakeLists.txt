list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ChangePasswordHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ChangePasswordHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ChangeEmailHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ChangeEmailHandler.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
