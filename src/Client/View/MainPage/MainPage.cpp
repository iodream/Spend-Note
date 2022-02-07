#include "MainPage.h"
#include "ui_MainPage.h"

#include "Exception.h"

MainPage::MainPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::MainPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->GoToListsButton,
		SIGNAL(clicked()),
		this,
		SLOT(OnGoToListsClicked()));

	connect(
		m_ui->LogoutButton,
		SIGNAL(clicked()),
		this,
		SLOT(OnLogoutClicked()));

	InitListsSubPage();
	InitCreateListSubPage();
}

void MainPage::InitListsSubPage()
{
	m_ui->Display->addWidget(&m_lists_spage);
}

void MainPage::InitCreateListSubPage()
{
	m_ui->Display->addWidget(&m_list_create_spage);
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

void MainPage::OnGoToListsClicked()
{
	emit ChangeSubPage(MainSubPages::LISTS);
}

void MainPage::OnLogoutClicked()
{
	emit Logout();
}
