#pragma once

#include "Controller/HTTPClient.h"

#include "ListPagesController.h"
#include "ProductPagesController.h"
#include "IncomePagesController.h"
#include "DailyListPageController.h"
#include "NavHistory.h"

#include "View/MainPage/MainPage.h"
#include "Common.h"
#include "View/Constants.h"

#include "Entities/PageData.h"

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


private:
	void ConnectPage();

	void InitListPagesController();
	void InitProductPagesController();
	void InitIncomePagesController();
	void InitDailyListPageController();

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


signals:
	void ChangePage(UIPages page);

public slots:
	void OnChangeSubPage(MainSubPages page, PageData data=PageData{});
	void OnUpdateSubPage(MainSubPages page, PageData data=PageData{});

	void OnServerError(const int code, const std::string& desc);
	void OnClientError(const std::string& desc);

	void OnGoBack(int n=1);
	void OnLogout();
};
