list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetListsHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetListsHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveListHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoveListHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Logger/Logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Logger/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Logger/ScopedLogger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Logger/ScopedLogger.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
