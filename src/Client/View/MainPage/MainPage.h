#pragma once

#include <map>

#include <QString>
#include <QWidget>

#include "List/ListsSubPage/ListsSubPage.h"
#include "List/ListCreateSubPage/ListCreateSubPage.h"
#include "List/ListEditSubPage/ListEditSubPage.h"
#include "List/ListViewSubPage/ListViewSubPage.h"

#include "Product/ProductsSubPage/ProductsSubPage.h"
#include "Product/ProductCreateSubPage/ProductCreateSubPage.h"
#include "Product/ProductEditSubPage/ProductEditSubPage.h"
#include "Product/ProductViewSubPage/ProductViewSubPage.h"

#include "Income/IncomesSubPage/IncomeListSubPage.h"
#include "Income/IncomeCreateSubPage/IncomeCreateSubPage.h"
#include "Income/IncomeViewSubPage/IncomeViewSubPage.h"

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

private:
	void InitListsSubPage();
	void InitListCreateSubPage();
	void InitListEditSubPage();
	void InitListViewSubPage();

	void InitProductsSubPage();
	void InitProductCreateSubPage();
	void InitProductEditSubPage();
	void InitProductViewSubPage();

	void InitIncomesSubPage();
	void InitIncomesCreateSubPage();

	void InitIncomeViewSubPage();

public:
	ListsSubPage& get_lists_spage() { return m_lists_spage; }
	ListCreateSubPage& get_list_create_spage() { return m_list_create_spage; }
	ListEditSubPage& get_list_edit_spage() { return m_list_edit_spage; }
	ListViewSubPage& get_list_view_spage() { return m_list_view_spage; }

	ProductsSubPage& get_products_spage() { return m_products_spage; }
	ProductCreateSubPage& get_product_create_spage() { return m_product_create_spage; }
	ProductEditSubPage& get_product_edit_spage() { return m_product_edit_spage; }
	ProductViewSubPage& get_product_view_spage() { return m_product_view_spage; }

	IncomeListSubPage& get_incomes_spage() { return m_incomes_spage; }
	IncomeCreateSubPage& get_incomes_create_spage() { return m_incomes_create_spage; }

	IncomeViewSubPage& get_income_view_spage() { return m_income_view_spage; }

private:
	Ui::MainPage *m_ui;

	ListsSubPage m_lists_spage;
	ListCreateSubPage m_list_create_spage;
	ListEditSubPage m_list_edit_spage;
	ListViewSubPage m_list_view_spage;

	ProductsSubPage m_products_spage;
	ProductCreateSubPage m_product_create_spage;
	ProductEditSubPage m_product_edit_spage;
	ProductViewSubPage m_product_view_spage;

	IncomeListSubPage m_incomes_spage;
	IncomeCreateSubPage m_incomes_create_spage;

	IncomeViewSubPage m_income_view_spage;

signals:
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void Logout();
	void GoBack(int n=1);

public slots:
	void OnGoToListsClicked();
	void OnGoToIncomesClicked();
	void OnLogoutClicked();
};
