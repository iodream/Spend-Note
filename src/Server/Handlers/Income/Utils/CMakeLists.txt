list(APPEND Spend-Note-Server_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoryUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeUtils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoryUtils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIdUtils.cpp
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
