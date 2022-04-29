#include "SettingsSubPage.h"
#include "ui_SettingsSubPage.h"

#include "View/MainPage/MainPage.h"

#include <QColorDialog>

int SettingsSubPage::CurColorElemSelected = 0;


SettingsSubPage::SettingsSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::SettingsSubPage)
{
	m_ui->setupUi(this);

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
	m_ui->frame->setStyleSheet("background-color:"+QString(MainPage::ColorSettings::COLOR_BALANCE_BANNER));
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

//default colors
void SettingsSubPage::OnColorScheme1Selected()
{
	MainPage::bNeedColorUpdate = true;

	MainPage::ColorSettings::WINDOW_BACKGROUND = "";
	MainPage::ColorSettings::LABEL_TEXT= "black";
	MainPage::ColorSettings::COLOR_BALANCE_BANNER= "#a3ffbc";
	MainPage::ColorSettings::ERROR_BANNER= "red";
	MainPage::ColorSettings::LIST_ACTIVE= "rgba(100, 230, 53, 50%)";
	MainPage::ColorSettings::LIST_INACTIVE= "rgba(37, 109, 217, 50%)";
	MainPage::ColorSettings::NAVBUTTONS= "#29baa7";
	MainPage::ColorSettings::PRODUCT_PRIO1= "rgba(201, 60, 32, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO2= "rgba(224, 133, 29, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO3= "rgba(202, 224, 31, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO4= "rgba(35, 217, 108, 50%)";
	MainPage::ColorSettings::PRODUCT_PRIO5= "rgba(25, 96, 209, 50%)";
	MainPage::ColorSettings::RECOMMENDATION= "#e38819";
	emit ColorSchemeChanged();
}

//dark mode
void SettingsSubPage::OnColorScheme2Selected()
{
	MainPage::bNeedColorUpdate = true;

	MainPage::ColorSettings::WINDOW_BACKGROUND = "#000000";
	MainPage::ColorSettings::LABEL_TEXT= "#f2eded";
	MainPage::ColorSettings::COLOR_BALANCE_BANNER= "#dbbe18";
	MainPage::ColorSettings::ERROR_BANNER= "#dbbe18";
	MainPage::ColorSettings::LIST_ACTIVE= "#dbbe18";
	MainPage::ColorSettings::LIST_INACTIVE= "#dbbe18";
	MainPage::ColorSettings::NAVBUTTONS= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO1= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO2= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO3= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO4= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO5= "#dbbe18";
	MainPage::ColorSettings::RECOMMENDATION= "#dbbe18";
	emit ColorSchemeChanged();
}

void SettingsSubPage::OnColorScheme3Selected()
{
	MainPage::bNeedColorUpdate = true;

	MainPage::ColorSettings::WINDOW_BACKGROUND = "#323ca8";
	MainPage::ColorSettings::LABEL_TEXT= "#dbbe18";
	MainPage::ColorSettings::COLOR_BALANCE_BANNER= "#dbbe18";
	MainPage::ColorSettings::ERROR_BANNER= "#dbbe18";
	MainPage::ColorSettings::LIST_ACTIVE= "#dbbe18";
	MainPage::ColorSettings::LIST_INACTIVE= "#dbbe18";
	MainPage::ColorSettings::NAVBUTTONS= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO1= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO2= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO3= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO4= "#dbbe18";
	MainPage::ColorSettings::PRODUCT_PRIO5= "#dbbe18";
	MainPage::ColorSettings::RECOMMENDATION= "#dbbe18";
	emit ColorSchemeChanged();
}

void SettingsSubPage::OnColorSchemeCustomSelect(int index)
{
	QString style = "background-color:";

	switch(index)
	{
	case 0:
		break;
	case 1:
		style += MainPage::ColorSettings::COLOR_BALANCE_BANNER;
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

void SettingsSubPage::OnNewColorSelected()
{
	MainPage::bNeedColorUpdate = true;
	QColor custom = QColorDialog::getColor();

	if(custom.isValid())
	{
		switch(m_ui->CustomColorsSelectBox->currentIndex())
		{
		case 0:
			MainPage::ColorSettings::WINDOW_BACKGROUND = custom.name();
			break;
		case 1:
			MainPage::ColorSettings::COLOR_BALANCE_BANNER = custom.name();
			break;
		case 2:
			MainPage::ColorSettings::NAVBUTTONS= custom.name();
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
