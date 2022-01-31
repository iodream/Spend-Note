list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Logger/Logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Logger/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Logger/ScopedLogger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Logger/ScopedLogger.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
