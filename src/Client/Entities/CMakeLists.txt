list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Formatters.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Parsers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PageData.h
)
set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
