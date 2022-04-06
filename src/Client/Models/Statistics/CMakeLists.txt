list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetBalanceModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsPerCategoryModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsPerCategoryModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsPercentagePerCategoryModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsPercentagePerCategoryModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsPerDayModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GetStatisticsPerDayModel.cpp
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
