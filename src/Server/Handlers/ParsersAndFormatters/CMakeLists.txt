list(APPEND Spend-Note-ParsersAndFormatter_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductFormat.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryParse.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryFormat.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdParse.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdFormat.h
)

set(Spend-Note-ParsersAndFormatters_SOURCES "${Spend-Note-ParsersAndFormatters_SOURCES}" PARENT_SCOPE)
