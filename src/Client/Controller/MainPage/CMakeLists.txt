list(APPEND Spend-Note-Client_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/MainPageController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MainPageController.h
	${CMAKE_CURRENT_SOURCE_DIR}/NavHistory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/NavHistory.h
	${CMAKE_CURRENT_SOURCE_DIR}/ListPagesController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ListPagesController.h
	${CMAKE_CURRENT_SOURCE_DIR}/ProductPagesController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductPagesController.h
	${CMAKE_CURRENT_SOURCE_DIR}/IncomePagesController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/IncomePagesController.h
	${CMAKE_CURRENT_SOURCE_DIR}/DailyListPageController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DailyListPageController.h
	${CMAKE_CURRENT_SOURCE_DIR}/StatisticsPageController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/StatisticsPageController.h
	${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoriesController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/IncomeCategoriesController.h
	${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoriesController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ProductCategoriesController.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SettingsPageController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SettingsPageController.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ProductRecommendationController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ProductRecommendationController.h
)

set(Spend-Note-Client_SOURCES "${Spend-Note-Client_SOURCES}" PARENT_SCOPE)
