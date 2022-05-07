list(APPEND Spend-Note-Client_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/ChangePasswordModel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ChangePasswordModel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ChangeEmailModel.h
	${CMAKE_CURRENT_SOURCE_DIR}/ChangeEmailModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
