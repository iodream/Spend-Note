list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoryJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONFormatter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductIdJSONFormatter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductJSONFormatter.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
