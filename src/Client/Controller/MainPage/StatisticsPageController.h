#pragma once

#include "Controller/HTTPClient.h"
#include "View/MainPage/Statistic/StatisticSubPage.h"
#include "Entities/PageData.h"
#include "View/Constants.h"

class StatisticsPageController : public QObject
{
	Q_OBJECT
public:
	StatisticsPageController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		StatisticSubPage& statistics_page);

	virtual ~StatisticsPageController() override {}

	bool UpdateStatisticsPage();

signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const std::string& desc);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void GoBack(int n=1);

public slots:
	void OnPercentChartSelected();
	void OnAmountChartSelected();
	void OnBalanceChartSelected();

private:
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	StatisticSubPage& m_statistics_page;

	void ConnectStatisticsPage();
	std::vector<ProductCategory> GetProductCategories();
};
