#include "SettingsSubPage.h"
#include "ui_SettingsSubPage.h"

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

void SettingsSubPage::SetEmail(const QString& email)
{
	m_ui->Email->setText(email);
	m_ui->CurrentEmail->setText(email);
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
	QString new_email = m_ui->NewEmailLineEdit->text();
	m_ui->NewEmailLineEdit->setText("");
	emit ChangeEmail(m_ui->Email->text(), new_email);
}

void SettingsSubPage::OnGoBackClicked()
{
	EraseLineEdits();
	GoToMainSubPage();
}
