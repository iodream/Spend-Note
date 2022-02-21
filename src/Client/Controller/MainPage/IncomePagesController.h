#pragma once

#include <QObject>

#include "Controller/HTTPClient.h"

#include "View/MainPage/Income/IncomesSubPage/IncomeListSubPage.h"
#include "View/MainPage/Income/IncomeCreateSubPage/IncomeCreateSubPage.h"
#include "View/MainPage/Income/IncomeEditSubPage/IncomeEditSubPage.h"
#include "View/MainPage/Income/IncomeViewSubPage/IncomeViewSubPage.h"
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
		IncomeListSubPage& incomes_page,
		IncomeViewSubPage& income_view_page);

	virtual ~IncomePagesController() override {}

	bool UpdateIncomesPage();
	bool UpdateIncomeViewPage(const PageData& data);
private:
	void ConnectIncomesPage();
	void ConnectIncomeViewPage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	IncomeListSubPage& m_incomes_page;
	//IncomeCreateSubPage& m_create_page;
	//IncomeEditSubPage& m_edit_page;
	IncomeViewSubPage& m_income_view_page;

	static bool already_added;
	void UpdateCategoryBoxes();
signals:
	void Message(const QString& window_name, const QString& message);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void UpdatePage(MainSubPages page, PageData data=PageData{});

	void GoBack(int n=1);

public slots:
	void OnGoToCreateIncome();
	void OnGoToViewIncome(const Income& income);

	void OnGoToEditIncome(const Income& income);
	void OnDeleteIncome(const Income& income);
};
