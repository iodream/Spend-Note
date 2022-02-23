#include "MainPage.h"
#include "ui_MainPage.h"

#include "Exception.h"

MainPage::MainPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::MainPage)
{
	m_ui->setupUi(this);

		m_ui->GoBackButton->setToolTip("Back");
		m_ui->GoToIncomesButton->setToolTip("My Incomes");
		m_ui->GoToListsButton->setToolTip("My Lists");
		m_ui->LogoutButton->setToolTip("Log Out");
		m_ui->Settings->setToolTip("Settings");


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


	connect(
		m_ui->CloseErrorBannerToolButton,
		&QToolButton::clicked,
		this,
		&MainPage::CloseErrorBanner);

	InitListsSubPage();
	InitListCreateSubPage();
	InitProductQuickCreateSubPage();

	InitListEditSubPage();
	InitListViewSubPage();

	InitProductsSubPage();
	InitProductCreateSubPage();
	InitProductEditSubPage();
	InitProductViewSubPage();

	InitIncomesSubPage();
	InitIncomesCreateSubPage();

	InitIncomeViewSubPage();
	InitIncomeEditPage();

}

void MainPage::InitListsSubPage()
{
	m_ui->Display->addWidget(&m_lists_spage);
}

void MainPage::InitListCreateSubPage()
{
	m_ui->Display->addWidget(&m_list_create_spage);
}

void MainPage::InitProductQuickCreateSubPage()
{
	m_ui->Display->addWidget(&m_product_quick_create_spage);
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

void MainPage::InitIncomesCreateSubPage()
{
	m_ui->Display->addWidget(&m_incomes_create_spage);
}

void MainPage::InitIncomeViewSubPage()
{
	m_ui->Display->addWidget(&m_income_view_spage);
}

void MainPage::InitIncomeEditPage()
{
	m_ui->Display->addWidget(&m_income_edit_spage);
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

void MainPage::SetErrorBanner(const int code, const std::string& description)
{
	m_ui->gridLayout_2->setRowStretch(2,1); // expands the banner
	m_ui->ErrorTitleLabel->setVisible(true);

	m_ui->ErrorCodeLabel->setText(QString::number(code));
	m_ui->ErrorDescriptionLabel->setText(QString::fromStdString(description));
}

void MainPage::SetErrorBanner(const std::string& description)
{
	m_ui->gridLayout_2->setRowStretch(2,1);
	m_ui->ErrorTitleLabel->setVisible(false);

	m_ui->ErrorCodeLabel->setText("");
	m_ui->ErrorDescriptionLabel->setText(QString::fromStdString(description));
}

void MainPage::CloseErrorBanner()
{
	m_ui->gridLayout_2->setRowStretch(2, 0); // set the banner to its minimum height
}
