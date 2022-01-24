#pragma once

#include <map>

#include <QString>
#include <QWidget>

#include "ListSubPage/ListSubPage.h"
#include "ListsPage/ListsPage.h"
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

	// next functions probably should be reimplemented when m_lists_page will be ready
	void SetCurrentSubPageList(ListSubPage::IdType id);
	void AddListSubPage(const QString& name, ListSubPage::IdType id);
	void RemoveListSubPage(ListSubPage::IdType id);
	void SetCurrentSubPage(int idx);


	ListsPage m_lists_page;

	Ui::MainPage *m_ui;
//	IncomesPage m_incomes_page;

	// probably should be removed when m_lists_page will be ready
	std::map<ListSubPage::IdType, ListSubPage*> m_list_sub_pages;

signals:
	void Logout();

public slots:
	void OnLogoutToolButtonClicked();
	void OnMainToolButtonClicked();
};
