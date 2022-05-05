list(APPEND Spend-Note-Client_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MainPage.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/RecommendationWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RecommendationWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RecommendationWidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/RecommendationItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RecommendationItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RecommendationItem.ui
)

add_subdirectory(List)
add_subdirectory(Product)
add_subdirectory(Income)
add_subdirectory(Statistic)
add_subdirectory(CategoryEditPage)
add_subdirectory(DailyList)
add_subdirectory(Settings)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
