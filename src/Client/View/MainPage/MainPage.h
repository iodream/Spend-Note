#pragma once

#include <map>

#include <QString>
#include <QWidget>

#include "List/ListsSubPage/ListsSubPage.h"
#include "List/ListCreateSubPage/ListCreateSubPage.h"
#include "List/ListEditSubPage/ListEditSubPage.h"
#include "List/ListViewSubPage/ListViewSubPage.h"
#include "List/ListCreateSubPage/ProductQuickCreateSubPage.h"

#include "Product/ProductsSubPage/ProductsSubPage.h"
#include "Product/ProductCreateSubPage/ProductCreateSubPage.h"
#include "Product/ProductEditSubPage/ProductEditSubPage.h"
#include "Product/ProductViewSubPage/ProductViewSubPage.h"

#include "Income/IncomesSubPage/IncomeListSubPage.h"
#include "Income/IncomeCreateSubPage/IncomeCreateSubPage.h"
#include "Income/IncomeViewSubPage/IncomeViewSubPage.h"
#include "Income/IncomeEditSubPage/IncomeEditSubPage.h"

#include "DailyList/DailyListSubPage/DailyListSubPage.h"
#include "Statistic/StatisticSubPage.h"
#include "CategoryEditPage/CategoryEditPage.h"

#include "View/Constants.h"

#include "Entities/PageData.h"


namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
	Q_OBJECT

public:
	explicit MainPage(QWidget *parent = nullptr);
	~MainPage();

	void SetCurrentSubPage(MainSubPages page);
	void SetCurrentSubPage(int idx);
	void ShowBalance(const Balance& money);

	void SetErrorBanner(const int code, const std::string& description);
	void SetErrorBanner(const std::string& description);
	void CloseErrorBanner();
	void changeEvent(QEvent* event);

private:
	void InitListsSubPage();
	void InitListCreateSubPage();
	void InitProductQuickCreateSubPage();
	void InitListEditSubPage();
	void InitListViewSubPage();

	void InitProductsSubPage();
	void InitProductCreateSubPage();
	void InitProductEditSubPage();
	void InitProductViewSubPage();

	void InitIncomesSubPage();
	void InitIncomesCreateSubPage();

	void InitIncomeViewSubPage();
	void InitIncomeEditPage();

	void InitDailyListSubPage();
	void InitStatisticsSubPage();
	void InitCategoriesEditSubPage();

public:
	ListsSubPage& get_lists_spage() { return m_lists_spage; }
	ListCreateSubPage& get_list_create_spage() { return m_list_create_spage; }
	ListEditSubPage& get_list_edit_spage() { return m_list_edit_spage; }
	ListViewSubPage& get_list_view_spage() { return m_list_view_spage; }
	ProductQuickCreateSubPage& get_product_quick_create_spage() { return m_product_quick_create_spage; }


	ProductsSubPage& get_products_spage() { return m_products_spage; }
	ProductCreateSubPage& get_product_create_spage() { return m_product_create_spage; }
	ProductEditSubPage& get_product_edit_spage() { return m_product_edit_spage; }
	ProductViewSubPage& get_product_view_spage() { return m_product_view_spage; }

	IncomeListSubPage& get_incomes_spage() { return m_incomes_spage; }
	IncomeCreateSubPage& get_incomes_create_spage() { return m_incomes_create_spage; }
	IncomeViewSubPage& get_income_view_spage() { return m_income_view_spage; }
	IncomeEditSubPage& get_income_edit_spage() { return m_income_edit_spage; }

	DailyListSubPage& get_daily_list_spage() { return m_dailylist_spage; }
	StatisticSubPage& get_statistics_spage() { return m_statistics_spage; }
	CategoryEditPage& get_categories_edit_spage() { return m_categories_edit_spage; }


private:
	Ui::MainPage *m_ui;

	ListsSubPage m_lists_spage;
	ListCreateSubPage m_list_create_spage;
	ProductQuickCreateSubPage m_product_quick_create_spage;
	ListEditSubPage m_list_edit_spage;
	ListViewSubPage m_list_view_spage;

	ProductsSubPage m_products_spage;
	ProductCreateSubPage m_product_create_spage;
	ProductEditSubPage m_product_edit_spage;
	ProductViewSubPage m_product_view_spage;

	IncomeListSubPage m_incomes_spage;
	IncomeCreateSubPage m_incomes_create_spage;

	IncomeViewSubPage m_income_view_spage;
	IncomeEditSubPage m_income_edit_spage;

	DailyListSubPage m_dailylist_spage;
	StatisticSubPage m_statistics_spage;
	CategoryEditPage m_categories_edit_spage;

signals:
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void Logout();
	void GoBack(int n=1);

public slots:
	void OnGoToListsClicked();
	void OnGoToIncomesClicked();
	void OnLogoutClicked();
	void OnGoToDailyListClicked();
	void OnGoToStatiticsClicked();
	void OnGoToCategoriesEditClicked();

};

