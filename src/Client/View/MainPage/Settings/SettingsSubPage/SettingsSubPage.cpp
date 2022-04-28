#include "SettingsSubPage.h"
#include "ui_SettingsSubPage.h"

#include "View/MainPage/MainPage.h"

#include <QColorDialog>

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
		m_ui->ColorColorsSelectBox,
		&QComboBox::currentIndexChanged,
		this,
		&SettingsSubPage::OnColorSchemeCustomSelect);
	connect(
		m_ui->CustomColorSchemeSave,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnCustomColorSchemeSaveAll);
	connect(
		m_ui->UseCustom,
		&QPushButton::clicked,
		this,
		&SettingsSubPage::OnUseCustomColorScheme);
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

void SettingsSubPage::OnColorScheme1Selected()
{
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

void SettingsSubPage::OnColorScheme2Selected()
{
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

void SettingsSubPage::OnColorScheme3Selected()
{
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
	auto custom = QColorDialog::getColor();
	if(custom.isValid())
	{
		switch(index)
		{
		case 1:
			MainPage::ColorSettings::WINDOW_BACKGROUND = custom.name();
			break;;
		case 2:
			MainPage::ColorSettings::COLOR_BALANCE_BANNER = custom.name();
			break;
		case 3:
			MainPage::ColorSettings::NAVBUTTONS= custom.name();
			break;
		case 4:
			MainPage::ColorSettings::ERROR_BANNER = custom.name();
			break;
		case 5:
			MainPage::ColorSettings::RECOMMENDATION = custom.name();
			break;
		case 6:
			MainPage::ColorSettings::LABEL_TEXT = custom.name();
			break;
		case 7:
			MainPage::ColorSettings::PRODUCT_PRIO1 = custom.name();
			break;
		case 8:
			MainPage::ColorSettings::PRODUCT_PRIO2 = custom.name();
			break;
		case 9:
			MainPage::ColorSettings::PRODUCT_PRIO3 = custom.name();
			break;
		case 10:
			MainPage::ColorSettings::PRODUCT_PRIO4 = custom.name();
			break;
		case 11:
			MainPage::ColorSettings::PRODUCT_PRIO5 = custom.name();
			break;
		case 12:
			MainPage::ColorSettings::LIST_ACTIVE = custom.name();
			break;
		case 13:
			MainPage::ColorSettings::LIST_INACTIVE = custom.name();
			break;
		}
	}
}

void SettingsSubPage::OnCustomColorSchemeSaveAll()
{
	emit SaveColorConfig();
}

void SettingsSubPage::OnUseCustomColorScheme()
{
	emit ColorSchemeChanged();
}
