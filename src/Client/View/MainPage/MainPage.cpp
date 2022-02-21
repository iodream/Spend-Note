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
		m_ui->GoToIncomesButton,
		&QPushButton::clicked,
		this,
		&MainPage::OnGoToIncomesClicked);

	connect(
		m_ui->LogoutButton,
		SIGNAL(clicked()),
		this,
		SLOT(OnLogoutClicked()));
	connect(
		m_ui->GoBackButton,
		SIGNAL(clicked()),
		this,
		SIGNAL(GoBack()));

	InitListsSubPage();
	InitListCreateSubPage();
	InitListEditSubPage();
	InitListViewSubPage();

	InitProductsSubPage();
	InitProductCreateSubPage();
	InitProductEditSubPage();
	InitProductViewSubPage();

	InitIncomesSubPage();
	InitIncomeViewSubPage();
}

void MainPage::InitListsSubPage()
{
	m_ui->Display->addWidget(&m_lists_spage);
}

void MainPage::InitListCreateSubPage()
{
	m_ui->Display->addWidget(&m_list_create_spage);
}

void MainPage::InitListEditSubPage()
{
	m_ui->Display->addWidget(&m_list_edit_spage);
}

void MainPage::InitListViewSubPage()
{
	m_ui->Display->addWidget(&m_list_view_spage);
}

void MainPage::InitProductsSubPage()
{
	m_ui->Display->addWidget(&m_products_spage);
}

void MainPage::InitProductCreateSubPage()
{
	m_ui->Display->addWidget(&m_product_create_spage);
}

void MainPage::InitProductEditSubPage()
{
	m_ui->Display->addWidget(&m_product_edit_spage);
}

void MainPage::InitProductViewSubPage()
{
	m_ui->Display->addWidget(&m_product_view_spage);
}

void MainPage::InitIncomesSubPage()
{
	m_ui->Display->addWidget(&m_incomes_spage);
}

void MainPage::InitIncomeViewSubPage()
{
	m_ui->Display->addWidget(&m_income_view_spage);
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

void MainPage::OnGoToIncomesClicked()
{
	emit ChangeSubPage(MainSubPages::INCOMES);
}

void MainPage::OnLogoutClicked()
{
	emit Logout();
}

void MainPage::ShowBalance(const Balance& money)
{
	m_ui->CurrentBalance->setText("Current Balance:  " + QString::number(money.balance));
	m_ui->ProjectedBalance->setText("Predicted balance:  " + QString::number(money.planned_balance));
}
