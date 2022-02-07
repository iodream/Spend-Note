#pragma once

#include <map>

#include <QString>
#include <QWidget>

#include "List/ListsSubPage/ListsSubPage.h"
#include "List/ListCreateSubPage/ListCreateSubPage.h"

#include "Product/ProductsSubPage/ProductsSubPage.h"

#include "View/Constants.h"


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

private:
	void InitListsSubPage();
	void InitCreateListSubPage();

public:
	ListsSubPage& get_lists_spage() { return m_lists_spage; }
	ListCreateSubPage& get_list_create_spage() { return m_list_create_spage; }

private:
	Ui::MainPage *m_ui;

	ListsSubPage m_lists_spage;
	ListCreateSubPage m_list_create_spage;

//	IncomesSubPage m_incomes_spage;

signals:
	void ChangeSubPage(MainSubPages page);
	void Logout();
	void GoBack();

public slots:
	void OnGoToListsClicked();
	void OnLogoutClicked();
};
