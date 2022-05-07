list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/PasswordUpdateJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PasswordUpdateJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TokenJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TokenJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/EmailUpdateJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EmailUpdateJSONParser.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
