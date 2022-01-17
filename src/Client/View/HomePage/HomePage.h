#pragma once

#include <map>

#include <QString>
#include <QWidget>

#include "ListPage/ListPage.h"
#include "View/Constants.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

	void SetCurrentPage(HomePages page);

	// next functions probably should be reimplemented when m_lists_page will be ready
	void SetCurrentPageList(ListPage::IdType id);
	void AddListPage(QString name, ListPage::IdType id);
	void RemoveListPage(ListPage::IdType id);

private:
	void SetCurrentPage(int idx);

	Ui::HomePage *ui;
//	ListsPage m_lists_page;
//	IncomesPage m_incomes_page;

	// probably should be removed when m_lists_page will be ready
	std::map<ListPage::IdType, ListPage*> m_list_pages;
};
