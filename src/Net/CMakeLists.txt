list(APPEND Spend-Note-Net_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Constants.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Message.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Parsing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parsing.h
)

list(APPEND Spend-Note-Net_LIBS
   QJsonObject
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
set(Spend-Note-Net_LIBS "${Spend-Note-Net_LIBS}" PARENT_SCOPE)
