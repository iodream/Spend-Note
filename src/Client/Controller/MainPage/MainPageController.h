#pragma once

#include "Controller/HTTPClient.h"

#include "ListPagesController.h"
#include "ProductPagesController.h"
#include "IncomePagesController.h"
#include "DailyListPageController.h"
#include "StatisticsPageController.h"
#include "IncomeCategoriesController.h"
#include "ProductCategoriesController.h"
#include "ProductRecommendationController.h"
#include "SettingsPageController.h"
#include "NavHistory.h"

#include "View/MainPage/MainPage.h"
#include "Common.h"
#include "View/Constants.h"

#include "Entities/PageData.h"

#include "View/MainPage/RecommendationWidget.h"

class MainPageController : public QObject
{
	Q_OBJECT
public:
	MainPageController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		MainPage& page);

	virtual ~MainPageController() override {}

	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void UpdateRecommendations();
	void ShowRecommendation();

private:
	void ConnectPage();

	void InitListPagesController();
	void InitProductPagesController();
	void InitProductRecommendationController();
	void InitIncomePagesController();
	void InitDailyListPageController();
	void InitStatisticsPageController();
	void InitIncomeCategoriesController();
	void InitProductCategoriesController();
	void InitSettingsPageController();


	bool UpdateSubPage(MainSubPages page, PageData data);

	std::optional<Balance> UpdateUserBalance(const IdType& id);

private:
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	MainPage& m_page;
	NavHistory m_history;

private:
	std::unique_ptr<ListPagesController> m_list_pages_controller;
	std::unique_ptr<ProductPagesController> m_product_pages_controller;
	std::unique_ptr<IncomePagesController> m_income_pages_controller;
	std::unique_ptr<DailyListPageController> m_daily_list_page_controller;
	std::unique_ptr<StatisticsPageController> m_statistics_page_controller;
	std::unique_ptr<IncomeCategoriesController> m_income_categories_controller;
	std::unique_ptr<ProductCategoriesController> m_product_categories_controller;
	std::unique_ptr<ProductRecommendationController> m_product_recommendation_controller;

	std::unique_ptr<SettingsPageController> m_settings_page_controller;

signals:
	void ChangePage(UIPages page);
	void SetEmail(const std::string& email);
	void ColorSchemeChanged();
	void SaveConfig();
	void LanguageChanged();
	void ScaleMinimumSize();

public slots:
	void OnChangeSubPage(MainSubPages page, PageData data=PageData{});
	void OnUpdateSubPage(MainSubPages page, PageData data=PageData{});
	void OnServerError(const int code, const std::string& desc);
	void OnClientError(const QString& desc);
	void OnGoBack(int n=1);
	void OnLogout();
	void OnFontChange();
	void OnUIUpdate();
	void OnRecommendationClosed();
};
