list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/TokenJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TokenJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PasswordUpdateJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PasswordUpdateJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/EmailUpdateJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EmailUpdateJSONFormatter.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
