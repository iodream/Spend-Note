list(APPEND Spend-Note-Logger_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ScopedLogger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ScopedLogger.cpp
)

set(Spend-Note-Logger_SOURCES "${Spend-Note-Logger_SOURCES}" PARENT_SCOPE)
