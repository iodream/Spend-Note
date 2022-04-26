list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/VerificationCodeFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VerificationCodeFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EmailSender.h
    ${CMAKE_CURRENT_SOURCE_DIR}/EmailSender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VerificationHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VerificationHandler.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
