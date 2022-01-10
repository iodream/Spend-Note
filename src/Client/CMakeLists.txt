list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTPClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Test.cpp
)

list(APPEND Spend-Note-Client_LIBS
    PocoNet
    PocoUtil
    PocoFoundation
    PocoJSON
)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Net ${CMAKE_CURRENT_BINARY_DIR}/Net)

list(APPEND Spend-Note-Client_SOURCES
    ${Spend-Note-Net_SOURCES}
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
set(Spend-Note-Client_LIBS "${Spend-Note-Client_LIBS}" PARENT_SCOPE)
