list(APPEND Spend-Note-ParsersAndFormatter_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdFormatter.h
)

set(Spend-Note-ParsersAndFormatters_SOURCES "${Spend-Note-ParsersAndFormatters_SOURCES}" PARENT_SCOPE)
