#include "SettingsSubPage.h"
#include "ui_SettingsSubPage.h"

#include "View/MainPage/MainPage.h"
#include <iostream>

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

void SettingsSubPage::OnColorSchemeCustom()
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
