#include "MainPage.h"
#include "ui_MainPage.h"

#include "Exception.h"

MainPage::MainPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::MainPage)
{
	m_ui->setupUi(this);

	connect(m_ui->mainToolButton, SIGNAL(clicked())
			, this, SLOT(OnMainToolButtonClicked()));

	connect(m_ui->settingsToolButton, SIGNAL(clicked())
			, this, SLOT(OnSettingsToolButtonClicked()));

	AddListSubPage("Some list 1", 1);
	// add income page here
	m_ui->Display->addWidget(&m_settings_page);
}

MainPage::~MainPage()
{
	delete m_ui;
}

void MainPage::SetCurrentSubPage(int idx)
{
	m_ui->Display->setCurrentIndex(idx);
}

void MainPage::SetCurrentSubPage(MainSubPages page)
{
	m_ui->Display->setCurrentIndex(static_cast<int>(page));
}

void MainPage::AddListSubPage(const QString& name, ListSubPage::IdType id)
{
	ListSubPage* page = new ListSubPage(name, id);
	auto insert_res = m_list_sub_pages.insert({id, page});
	if (!insert_res.second)
		throw Exception("List page with specified id already exists");
	m_ui->Display->addWidget(page);
}

void MainPage::RemoveListSubPage(ListSubPage::IdType id)
{
	auto it = m_list_sub_pages.find(id);
	if (it == m_list_sub_pages.end())
		throw Exception("No page with such id");
	ListSubPage* page = it->second;
	m_ui->Display->removeWidget(page);
	delete page;
	m_list_sub_pages.erase(it);
}

void MainPage::SetCurrentSubPageList(ListSubPage::IdType id)
{
	try {
		ListSubPage* page = m_list_sub_pages.at(id);
		auto idx = m_ui->Display->indexOf(page);
		SetCurrentSubPage(idx);
	}  catch (const std::out_of_range& ex) {
		throw Exception(ex.what());
	}
}

void MainPage::OnMainToolButtonClicked()
{
	SetCurrentSubPage(0); // currently 0
	// but value should be changed to MainSubPages::LISTS later
}

void MainPage::OnSettingsToolButtonClicked()
{
	SetCurrentSubPage(1); // currently 1
	// but value should be changed to MainSubPages::SETTINGS later
}
