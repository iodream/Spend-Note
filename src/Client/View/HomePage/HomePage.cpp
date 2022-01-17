#include "HomePage.h"
#include "ui_HomePage.h"

#include "Exception.h"

HomePage::HomePage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HomePage)
{
    ui->setupUi(this);
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::SetCurrentPage(int idx)
{
	ui->Display->setCurrentIndex(idx);
}

void HomePage::SetCurrentPage(HomePages page)
{
	ui->Display->setCurrentIndex(static_cast<int>(page));
}

void HomePage::AddListPage(QString name, ListPage::IdType id)
{
	ListPage* page = new ListPage(name, id);
	auto insert_res = m_list_pages.insert({id, page});
	if (!insert_res.second)
		throw Exception("List page with specified id already exists");
	ui->Display->addWidget(page);
}

void HomePage::RemoveListPage(ListPage::IdType id)
{
	auto it = m_list_pages.find(id);
	if (it == m_list_pages.end())
		throw Exception("No page with such id");
	ListPage* page = it->second;
	ui->Display->removeWidget(page);
	delete page;
	m_list_pages.erase(it);
}

void HomePage::SetCurrentPageList(ListPage::IdType id)
{
	try {
		ListPage* page = m_list_pages.at(id);
		auto idx = ui->Display->indexOf(page);
		SetCurrentPage(idx);
	}  catch (const std::out_of_range& ex) {
		throw Exception(ex.what());
	}
}
