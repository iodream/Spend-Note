list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ArrayJSONParserBase.h
)

add_subdirectory(Income)
add_subdirectory(List)
add_subdirectory(Product)
add_subdirectory(Statistics)
add_subdirectory(PeriodicProduct)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
