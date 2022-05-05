#include "MainPage.h"
#include "ui_MainPage.h"

#include "Exception.h"
#include <QColorDialog>

QString MainPage::ColorSettings::COLOR_TOP_BANNER = "#a3ffbc";
QString MainPage::ColorSettings::NAVBUTTONS = "#29baa7";
QString MainPage::ColorSettings::RECOMMENDATION = "rgba(227, 136, 25)";
QString MainPage::ColorSettings::ERROR_BANNER = "#ef2929";
QString MainPage::ColorSettings::WINDOW_BACKGROUND = "";
QString MainPage::ColorSettings::LABEL_TEXT = "black";
QString MainPage::ColorSettings::PRODUCT_PRIO1 = "rgba(201, 60, 32, 50%)";
QString MainPage::ColorSettings::PRODUCT_PRIO2 = "rgba(224, 133, 29, 50%)";
QString MainPage::ColorSettings::PRODUCT_PRIO3 = "rgba(202, 224, 31, 50%)";
QString MainPage::ColorSettings::PRODUCT_PRIO4 = "rgba(35, 217, 108, 50%)";
QString MainPage::ColorSettings::PRODUCT_PRIO5 = "rgba(25, 96, 209, 50%)";
QString MainPage::ColorSettings::LIST_INACTIVE = "rgba(163, 255, 188, 50%)";
QString MainPage::ColorSettings::LIST_ACTIVE = "rgba(37, 109, 217, 50%)";

QFont MainPage::UISettings::UI_FONT;
bool MainPage::bNeedsGlobalUIUpdate = true;

MainPage::MainPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::MainPage)
{
	m_ui->setupUi(this);

		m_ui->GoBackButton->setToolTip("Back");
		m_ui->GoToIncomesButton->setToolTip("My Incomes");
		m_ui->GoToListsButton->setToolTip("My Lists");
		m_ui->LogoutButton->setToolTip("Log Out");
		m_ui->GoToDailyList->setToolTip("Daily List");
		m_ui->GoToSettingsButton->setToolTip("Settings");
		m_ui->GoToStatisticsButton->setToolTip("Statistics");
		m_ui->GoToCategoriesButton->setToolTip("My Categories");

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
		m_ui->GoToDailyList,
		&QPushButton::clicked,
		this,
		&MainPage::OnGoToDailyListClicked);

	connect(
		m_ui->GoToStatisticsButton,
		&QPushButton::clicked,
		this,
		&MainPage::OnGoToStatiticsClicked);

	connect(
		m_ui->GoToCategoriesButton,
		&QPushButton::clicked,
		this,
		&MainPage::OnGoToCategoriesEditClicked);

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

	connect(
		m_ui->GoToSettingsButton,
		&QToolButton::clicked,
		this,
		&MainPage::OnGoToSettingsClicked);

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

	InitDailyListSubPage();
	InitStatisticsSubPage();
	InitCategoriesEditSubPage();
	InitSettingsSubPage();

	recommendation_widget = std::make_shared<RecommendationWidget>(this);
	recommendation_item = std::make_shared<RecommendationItem>("", List(), recommendation_widget.get());

	connect(
		recommendation_widget.get(),
		&RecommendationWidget::RecommendationClosed,
		this,
		&MainPage::OnRecommendationClosed);
}

void MainPage::resizeEvent(QResizeEvent *event)
{
	//position it in lower right corner
	recommendation_widget->move(size().width() - recommendation_widget->size().width() - 25,
			  size().height() - recommendation_widget->size().height() - 25);
	QWidget::resizeEvent(event);
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

void MainPage::InitDailyListSubPage()
{
	m_ui->Display->addWidget(&m_dailylist_spage);
}

void MainPage::InitStatisticsSubPage()
{
	m_ui->Display->addWidget(&m_statistics_spage);
}

void MainPage::InitCategoriesEditSubPage()
{
	m_ui->Display->addWidget(&m_categories_edit_spage);
}


void MainPage::HideRecommendation()
{
	recommendation_widget->hide();
}

void MainPage::InitSettingsSubPage()
{
	m_ui->Display->addWidget(&m_settings_spage);
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

void MainPage::OnGoToDailyListClicked()
{
	emit ChangeSubPage(MainSubPages::DAILY_LIST);
}

void MainPage::OnGoToStatiticsClicked()
{
	emit ChangeSubPage(MainSubPages::STATISTICS);
}

void MainPage::OnGoToCategoriesEditClicked()
{
	emit ChangeSubPage(MainSubPages::CATEGORIES_EDIT);
}

void MainPage::OnRecommendationClosed()
{
	emit RecommendationClosed();
}

void MainPage::OnGoToSettingsClicked()
{
	emit ChangeSubPage(MainSubPages::SETTINGS);
}

void MainPage::ShowBalance(const Balance& money)
{
	m_ui->CurrentBalance->setText("Current Balance:  " + QString::number(money.balance));
	m_ui->ProjectedBalance->setText("Predicted balance:  " + QString::number(money.planned_balance));
}

//top-lvl changes are done here
// need a unified function for now because setStyleSheet always wipes everything else
void MainPage::UpdatePage()
{
	//balance banners
	m_ui->BalanceHolder->setStyleSheet(QString("background-color:" + ColorSettings::COLOR_TOP_BANNER));

	//general text and font size
	setStyleSheet(QString("color:%1; font-family:%2; font-size:%3px")
						  .arg(ColorSettings::LABEL_TEXT)
						  .arg(MainPage::UISettings::UI_FONT.family())
						  .arg(MainPage::UISettings::UI_FONT.pointSize()));

	//recommendation widget
	recommendation_widget->setStyleSheet(QString("background-color:" + ColorSettings::RECOMMENDATION));

	//general text
	setStyleSheet(QString("color:" + ColorSettings::LABEL_TEXT));	

	//nav buttons
	QList<QToolButton*> list = m_ui->NavigationBar->findChildren<QToolButton*>();
	foreach(auto obj, list)
	{
		obj->setStyleSheet(QString("background-color:" + ColorSettings::NAVBUTTONS));
	}
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

void MainPage::UpdateRecommendation(const List& list)
{
	recommendation_item = std::make_shared<RecommendationItem>(list.name, list, recommendation_widget.get());

	connect(
		recommendation_item.get(),
		&RecommendationItem::clicked,
		this,
		&MainPage::OnRecommendationClicked);

	recommendation_widget->RemoveItem();
	recommendation_widget->AppendItem(recommendation_item.get());
}

void MainPage::OnRecommendationClicked()
{
	emit GoToProducts(recommendation_item->get_list());
}
