list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/List.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Product.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductId.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ProductCategory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Income.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IncomeId.h
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
