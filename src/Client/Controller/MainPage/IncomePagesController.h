#pragma once

#include <QObject>

#include "Controller/HTTPClient.h"

#include "View/MainPage/Income/IncomesSubPage/IncomeListSubPage.h"
#include "View/Constants.h"

#include "Entities/PageData.h"

class IncomePagesController : public QObject
{
	Q_OBJECT
public:
	explicit IncomePagesController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		IncomeListSubPage& incomes_page);

	virtual ~IncomePagesController() override {}

	bool UpdateIncomesPage();
private:
	void ConnectIncomesPage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	IncomeListSubPage& m_incomes_page;

signals:
	void Error(const int code, const std::string& desc);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void UpdatePage(MainSubPages page, PageData data=PageData{});

	void GoBack(int n=1);

public slots:
	void OnGoToCreateIncome();
	void OnGoToViewIncome(const Income& income);
};
