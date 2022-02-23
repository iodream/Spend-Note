list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.ui
)

add_subdirectory(List)
add_subdirectory(Product)
add_subdirectory(Income)
add_subdirectory(Statistic)
add_subdirectory(DailyList)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
