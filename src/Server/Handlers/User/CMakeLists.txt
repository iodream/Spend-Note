list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ChangePasswordHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ChangePasswordHandler.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
