list(APPEND Spend-Note-Net_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/EmailUpdate.h
  ${CMAKE_CURRENT_SOURCE_DIR}/PasswordUpdate.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Token.h
)

set(Spend-Note-Net_SOURCES "${Spend-Note-Net_SOURCES}" PARENT_SCOPE)
