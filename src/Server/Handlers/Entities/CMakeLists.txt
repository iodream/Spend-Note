list(APPEND Spend-Note-Server_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Formatters.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Parsers.h
)
set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
