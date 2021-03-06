#include "MainPage.h"
#include "ui_MainPage.h"

#include "Exception.h"
#include <QColorDialog>


QString MainPage::ColorSettings::COLOR_TOP_BANNER = "rgba(163, 255, 188, 100%)";
QString MainPage::ColorSettings::NAVBUTTONS = "rgba(41, 186, 167, 50%)";
QString MainPage::ColorSettings::RECOMMENDATION = "rgba(232, 151, 12, 100%)";
QString MainPage::ColorSettings::ERROR_BANNER = "rgba(239, 41, 41, 100%)";
QString MainPage::ColorSettings::WINDOW_BACKGROUND = "";
QString MainPage::ColorSettings::LABEL_TEXT = "rgba(0, 0, 0, 100%)";

QString MainPage::ColorSettings::PRODUCT_PRIO1 = "rgba(201, 60, 32, 50%)";
QString MainPage::ColorSettings::PRODUCT_PRIO2 = "rgba(224, 133, 29, 50%)";
QString MainPage::ColorSettings::PRODUCT_PRIO3 = "rgba(202, 224, 31, 50%)";
QString MainPage::ColorSettings::PRODUCT_PRIO4 = "rgba(35, 217, 108, 50%)";
QString MainPage::ColorSettings::PRODUCT_PRIO5 = "rgba(25, 96, 209, 50%)";
QString MainPage::ColorSettings::LIST_INACTIVE = "rgba(163, 255, 188, 50%)";
QString MainPage::ColorSettings::LIST_ACTIVE = "rgba(37, 109, 217, 50%)";

UILangs MainPage::UISettings::LANG_UI = UILangs::AMERICAN_ENGLISH;

const std::map<UILangs, QString> MainPage::UISettings::translation_file{
	{UILangs::AMERICAN_ENGLISH, "en_US"},
	{UILangs::UKRAINIAN, "uk_UA"},
};

QFont MainPage::UISettings::UI_FONT;
QFont MainPage::UISettings::UI_DEFAULT_FONT = QFont("Sans Serif", 11);

const float MainPage::UISettings::WINDOW_SCALE_FACTOR_X = 50;
const float MainPage::UISettings::WINDOW_SCALE_FACTOR_Y = 40;

bool MainPage::bNeedsGlobalUIUpdate = true;

MainPage::MainPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::MainPage)
{
	m_ui->setupUi(this);
	m_ui->ErrorBanner->setVisible(false);

	m_ui->GoBackButton->setToolTip(tr("Back"));
	m_ui->GoToIncomesButton->setToolTip(tr("My Incomes"));
	m_ui->GoToListsButton->setToolTip(tr("My Lists"));
	m_ui->LogoutButton->setToolTip(tr("Log Out"));
	m_ui->GoToDailyList->setToolTip(tr("Daily List"));
	m_ui->GoToSettingsButton->setToolTip(tr("Settings"));
	m_ui->GoToStatisticsButton->setToolTip(tr("Statistics"));
	m_ui->GoToCategoriesButton->setToolTip(tr("My Categories"));

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

	connect(
		recommendation_widget.get(),
		&RecommendationWidget::RecommendationClosed,
		this,
		&MainPage::OnRecommendationClosed);

	connect(
		recommendation_widget.get(),
		&RecommendationWidget::GoToProductView,
		this,
		&MainPage::GoToProductView);
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

void MainPage::ShowRecommendation()
{
	recommendation_widget->show();
}

void MainPage::InitSettingsSubPage()
{
	m_ui->Display->addWidget(&m_settings_spage);
}

MainPage::~MainPage()
{
	delete m_ui;
}

void MainPage::changeEvent(QEvent* event)
{
	if(event)
	{
		switch(event->type())
		{
		case QEvent::LanguageChange:
			m_ui->retranslateUi(this);
			m_ui->GoBackButton->setToolTip(tr("Back"));
			m_ui->GoToIncomesButton->setToolTip(tr("My Incomes"));
			m_ui->GoToListsButton->setToolTip(tr("My Lists"));
			m_ui->LogoutButton->setToolTip(tr("Log Out"));
			m_ui->GoToDailyList->setToolTip(tr("Daily List"));
			m_ui->GoToSettingsButton->setToolTip(tr("Settings"));
			m_ui->GoToStatisticsButton->setToolTip(tr("Statistics"));
			m_ui->GoToCategoriesButton->setToolTip(tr("My Categories"));
			break;
		}

		QWidget::changeEvent(event);
	}
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
	m_ui->CurrentBalance->setText(tr("Current Balance:  ") + QString::number(money.balance));
	m_ui->ProjectedBalance->setText(tr("Predicted balance:  ") + QString::number(money.planned_balance));
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

	//nav buttons
	QList<QToolButton*> list = m_ui->NavigationBar->findChildren<QToolButton*>();
	foreach(auto obj, list)
	{
		obj->setStyleSheet(QString("background-color:" + ColorSettings::NAVBUTTONS));
	}
}

void MainPage::SetErrorBanner(const int code, const std::string& description)
{
	m_ui->ErrorTitleLabel->setVisible(true);
	m_ui->ErrorBanner->setVisible(true);

	m_ui->ErrorCodeLabel->setText(QString::number(code));
	m_ui->ErrorDescriptionLabel->setText(QString::fromStdString(description));
}

void MainPage::SetErrorBanner(const QString& description)
{
	m_ui->ErrorTitleLabel->setVisible(false);
	m_ui->ErrorBanner->setVisible(true);

	m_ui->ErrorCodeLabel->setText("");
	m_ui->ErrorDescriptionLabel->setText(description);
}

void MainPage::CloseErrorBanner()
{
	m_ui->ErrorBanner->setVisible(false);
}

void MainPage::UpdateRecommendation(const Product& product)
{
	recommendation_widget->Clear();
	ProductItem* it = new ProductItem(product);
	recommendation_widget->AppendProduct(it);
		connect(
			recommendation_widget.get(),
			&RecommendationWidget::GoToProductView,
			this,
			&MainPage::OnRecommendationClicked);
}

void MainPage::OnRecommendationClicked(const Product& product)
{
	HideRecommendation();
	PageData data{};
	data.setValue(product);
	emit ChangeSubPage(MainSubPages::VIEW_PRODUCT, data);
}

QFont MainPage::UISettings::GetDefaultFont()
{
	return UI_DEFAULT_FONT;
}
