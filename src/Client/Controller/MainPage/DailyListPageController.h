#pragma once

#include <QObject>

#include "Controller/HTTPClient.h"

#include "View/MainPage/DailyList/DailyListSubPage/DailyListSubPage.h"
#include "Models/List/GetDailyListModel.h"

#include "View/Constants.h"
#include "Entities/PageData.h"

class DailyListPageController : public QObject
{
	Q_OBJECT
public:
	explicit DailyListPageController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		DailyListSubPage& daily_list_page);

	virtual ~DailyListPageController() override {}

	bool UpdateDailyListPage();
	void UpdatePageColors();

private:
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	DailyListSubPage& m_daily_list_page;

	void ConnectDailyListPage();

signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const QString& desc);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void UpdatePage(MainSubPages page, PageData data=PageData{});

	void GoBack(int n=1);

public slots:
	void OnGoToProductView(const Product& product);
};
