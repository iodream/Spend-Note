list(APPEND Spend-Note-Server_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeIn.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeId.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IncomeOut.h
)

set(Spend-Note-Server_SOURCES "${Spend-Note-Server_SOURCES}" PARENT_SCOPE)
