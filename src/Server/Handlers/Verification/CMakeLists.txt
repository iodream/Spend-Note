list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/VerificationCodeFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VerificationCodeFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EmailSender.h
    ${CMAKE_CURRENT_SOURCE_DIR}/EmailSender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CheckVerificationHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CheckVerificationHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AddVerificationHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AddVerificationHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SSLInitializer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SSLInitializer.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
