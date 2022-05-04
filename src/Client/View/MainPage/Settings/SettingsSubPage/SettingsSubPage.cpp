#include "SettingsSubPage.h"
#include "ui_SettingsSubPage.h"

#include <QFontDialog>
#include "View/MainPage/MainPage.h"
#include <QColorDialog>

int SettingsSubPage::CurColorElemSelected = 0;

SettingsSubPage::SettingsSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::SettingsSubPage)
{
	m_ui->setupUi(this);

	Update();

	connect(
		m_ui->ChangePasswordButton,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnChangePasswordButtonClicked);

	connect(
		m_ui->ChangeEmailButton,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnChangeEmailButtonClicked);

	connect(
		m_ui->SubmitPasswordChangeButton,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnSubmitPasswordChangeButtonClicked);

	connect(
		m_ui->SubmitEmailChangeButton,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnSubmitEmailChangeButtonClicked);

	connect(
		m_ui->GoBackButton,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnGoBackClicked);

	connect(
		m_ui->GoBackButton_2,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnGoBackClicked);

	connect(
		m_ui->FontSelectButton,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnFontChange);

	connect(
		m_ui->DefaultFontButton,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnDefaultFontClicked);

	connect(
		m_ui->FontSpinBox,
		&QSpinBox::valueChanged,
		this,
		&SettingsSubPage::FontSizeChange);
	connect(
		m_ui->Scheme1,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnColorScheme1Selected);

	connect(
		m_ui->Scheme2,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnColorScheme2Selected);

	connect(
		m_ui->Scheme3,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnColorScheme3Selected);
	connect(
		m_ui->CustomColorsSelectBox,
		&QComboBox::activated,
		this,
		&SettingsSubPage::OnColorSchemeCustomSelect);

	connect(
		m_ui->OpenColorSelector,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnNewColorSelected);
}

SettingsSubPage::~SettingsSubPage()
{
	delete m_ui;
}

void SettingsSubPage::EraseLineEdits()
{
	m_ui->NewEmailLineEdit->setText("");
	m_ui->OldPasswordLineEdit->setText("");
	m_ui->NewPasswordLineEdit->setText("");
	m_ui->RepeatNewPasswordLineEdit->setText("");
}

void SettingsSubPage::GoToMainSubPage()
{
	m_ui->stackedWidget->setCurrentIndex(0);
}

void SettingsSubPage::OnChangePasswordButtonClicked()
{
	m_ui->stackedWidget->setCurrentIndex(1);
}

void SettingsSubPage::UpdateColors()
{
	m_ui->frame->setStyleSheet("background-color:" + QString(MainPage::ColorSettings::COLOR_TOP_BANNER));
	m_ui->UserInfoLabel_2->setStyleSheet("background-color: " + MainPage::ColorSettings::COLOR_TOP_BANNER);
	m_ui->ColorSchemeLabel->setStyleSheet("background-color: " + MainPage::ColorSettings::COLOR_TOP_BANNER);
	m_ui->FontsLabel->setStyleSheet("background-color: " + MainPage::ColorSettings::COLOR_TOP_BANNER);
}

void SettingsSubPage::OnChangeEmailButtonClicked()
{
	m_ui->stackedWidget->setCurrentIndex(2);
}

void SettingsSubPage::OnSubmitPasswordChangeButtonClicked()
{
	EraseLineEdits();
	GoToMainSubPage(); // return back, mocked right now
}

void SettingsSubPage::OnSubmitEmailChangeButtonClicked()
{
	m_ui->NewEmailLineEdit->setText("");
	GoToMainSubPage(); // also mocked
}

void SettingsSubPage::OnGoBackClicked()
{
	EraseLineEdits();
	GoToMainSubPage();
}

// font selection
void SettingsSubPage::OnFontChange()
{
	MainPage::bNeedsGlobalUIUpdate = true;

	QFont font = QFontDialog::getFont(nullptr, QFont("Sans Serif", 11)); //use this font if cancel is pressed
	MainPage::UISettings::UI_FONT = font;

	emit FontChange();
	Update();
}

void SettingsSubPage::Update()
{
	m_ui->CurrentFontLabel->setText(QString(tr("Current font is: %1 %2"))
								  .arg(MainPage::UISettings::UI_FONT.family())
								  .arg(QString::number(MainPage::UISettings::UI_FONT.pointSize())));

	m_ui->FontSpinBox->setValue(MainPage::UISettings::UI_FONT.pointSize());
}

//default colors
void SettingsSubPage::OnColorScheme1Selected()
{
	MainPage::bNeedsGlobalUIUpdate = true;

	MainPage::ColorSettings::WINDOW_BACKGROUND = "";
	MainPage::ColorSettings::LABEL_TEXT= "black";
	MainPage::ColorSettings::COLOR_TOP_BANNER= "#a3ffbc";
	MainPage::ColorSettings::ERROR_BANNER= "#ef2929";
	MainPage::ColorSettings::LIST_ACTIVE= "rgba(100, 230, 53, 50%)";
	MainPage::ColorSettings::LIST_INACTIVE= "rgba(37, 109, 217, 50%)";
	MainPage::ColorSettings::NAVBUTTONS= "#29baa7";
	MainPage::ColorSettings::RECOMMENDATION= "#e8970c";

	//set in rgba to specify transparency
	MainPage::ColorSettings::PRODUCT_PRIO1= "rgba(201, 60, 32, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO2= "rgba(224, 133, 29, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO3= "rgba(202, 224, 31, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO4= "rgba(35, 217, 108, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO5= "rgba(25, 96, 209, 50%)";

	emit ColorSchemeChanged();
}

//dark mode
void SettingsSubPage::OnColorScheme2Selected()
{
	MainPage::bNeedsGlobalUIUpdate = true;

	MainPage::ColorSettings::WINDOW_BACKGROUND = "#334257";
	MainPage::ColorSettings::LABEL_TEXT= "#eeeeee";
	MainPage::ColorSettings::COLOR_TOP_BANNER= "#5584ac";
	MainPage::ColorSettings::ERROR_BANNER= "#990909";
	MainPage::ColorSettings::LIST_ACTIVE= "#5b9bd5";
	MainPage::ColorSettings::LIST_INACTIVE= "#92a9bd";
	MainPage::ColorSettings::NAVBUTTONS= "#406882";
	MainPage::ColorSettings::PRODUCT_PRIO1= "rgba(153, 9, 9, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO2= "rgba(197, 90, 17, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO3= "rgba(191, 144, 0, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO4= "rgba(84, 130, 53, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO5= "rgba(47, 85, 151, 50%)";
	MainPage::ColorSettings::RECOMMENDATION= "rgba(105, 152, 171, 50%)";

	emit ColorSchemeChanged();
}

//winter day colors
void SettingsSubPage::OnColorScheme3Selected()
{
	MainPage::bNeedsGlobalUIUpdate = true;

	MainPage::ColorSettings::WINDOW_BACKGROUND = "#edf7fa";
	MainPage::ColorSettings::LABEL_TEXT= "black";
	MainPage::ColorSettings::COLOR_TOP_BANNER= "#8faadc";
	MainPage::ColorSettings::ERROR_BANNER= "#ef2929";
	MainPage::ColorSettings::LIST_ACTIVE= "#ffe699";
	MainPage::ColorSettings::LIST_INACTIVE= "#9dc3e6";
	MainPage::ColorSettings::NAVBUTTONS= "#9dc3e6";
	MainPage::ColorSettings::PRODUCT_PRIO1= "rgba(255, 122, 91, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO2= "rgba(243, 168, 117, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO3= "rgba(255, 204, 102, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO4= "rgba(169, 209, 142, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO5= "rgba(143, 170, 220, 50%)";
	MainPage::ColorSettings::RECOMMENDATION= "rgba(143, 170, 220, 50%)";

	emit ColorSchemeChanged();
}

//dropdown box with elements
void SettingsSubPage::OnColorSchemeCustomSelect(int index)
{
	QString style = "background-color:";

	switch(index)
	{
	case 0:
		break;
	case 1:
		style += MainPage::ColorSettings::COLOR_TOP_BANNER;
		break;
	case 2:
		style += MainPage::ColorSettings::NAVBUTTONS;
		break;
	case 3:
		style += MainPage::ColorSettings::ERROR_BANNER;
		break;
	case 4:
		style += MainPage::ColorSettings::RECOMMENDATION;
		break;
	case 5:
		style += MainPage::ColorSettings::LABEL_TEXT;
		break;
	case 6:
		style += MainPage::ColorSettings::PRODUCT_PRIO1;
		break;
	case 7:
		style += MainPage::ColorSettings::PRODUCT_PRIO2;
		break;
	case 8:
		style += MainPage::ColorSettings::PRODUCT_PRIO3;;
		break;
	case 9:
		style += MainPage::ColorSettings::PRODUCT_PRIO4;
		break;
	case 10:
		style += MainPage::ColorSettings::PRODUCT_PRIO5;
		break;
	case 11:
		style += MainPage::ColorSettings::LIST_ACTIVE;
		break;
	case 12:
		style += MainPage::ColorSettings::LIST_INACTIVE;
		break;
	}
	m_ui->ElemenColor->setStyleSheet(style);
}

//custom color selection
void SettingsSubPage::OnNewColorSelected()
{
	MainPage::bNeedsGlobalUIUpdate = true;
	QColor custom = QColorDialog::getColor();

	if(custom.isValid())
	{
		switch(m_ui->CustomColorsSelectBox->currentIndex())
		{
		case 0:
			MainPage::ColorSettings::WINDOW_BACKGROUND = custom.name();
			break;
		case 1:
			MainPage::ColorSettings::COLOR_TOP_BANNER = custom.name();
			break;
		case 2:
			MainPage::ColorSettings::NAVBUTTONS = custom.name();
			break;
		case 3:
			MainPage::ColorSettings::ERROR_BANNER = custom.name();
			break;
		case 4:
			MainPage::ColorSettings::RECOMMENDATION = custom.name();
			break;
		case 5:
			MainPage::ColorSettings::LABEL_TEXT = custom.name();
			break;
		case 6:
			custom.setAlphaF(0.5);
			MainPage::ColorSettings::PRODUCT_PRIO1 = custom.name(QColor::HexArgb);
			break;
		case 7:
			custom.setAlphaF(0.5);
			MainPage::ColorSettings::PRODUCT_PRIO2 = custom.name(QColor::HexArgb);
			break;
		case 8:
			custom.setAlphaF(0.5);
			MainPage::ColorSettings::PRODUCT_PRIO3 = custom.name(QColor::HexArgb);
			break;
		case 9:
			custom.setAlphaF(0.5);
			MainPage::ColorSettings::PRODUCT_PRIO4 = custom.name(QColor::HexArgb);
			break;
		case 10:
			custom.setAlphaF(0.5);
			MainPage::ColorSettings::PRODUCT_PRIO5 = custom.name(QColor::HexArgb);
			break;
		case 11:
			custom.setAlphaF(0.5);
			MainPage::ColorSettings::LIST_ACTIVE = custom.name(QColor::HexArgb);
			break;
		case 12:
			custom.setAlphaF(0.5);
			MainPage::ColorSettings::LIST_INACTIVE = custom.name(QColor::HexArgb);
			break;
		}
	}
	OnColorSchemeCustomSelect(m_ui->CustomColorsSelectBox->currentIndex());
	emit ColorSchemeChanged();
}

void SettingsSubPage::OnDefaultFontClicked()
{
	MainPage::UISettings::UI_FONT = QFont("Sans Serif", 11);
	Update();
	emit FontChange();
}

// font size change from spinbox
void SettingsSubPage::FontSizeChange(int size)
{
	MainPage::UISettings::UI_FONT.setPointSize(size);
	emit FontChange();
}
