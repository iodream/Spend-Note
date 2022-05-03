#include "SignupPage.h"
#include "ui_SignupPage.h"

SignupPage::SignupPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::SignupPage)
{
	m_ui->setupUi(this);

	m_ui->ErrorWidget->setVisible(false);

	connect(
		m_ui->SignupSubmitButton,
		&QPushButton::released,
		this,
		&SignupPage::OnSignupSubmitButtonClicked);

	connect(
		m_ui->GoBackButton,
		&QPushButton::released,
		this,
		&SignupPage::GoToLoginPage);

	connect(
		m_ui->CloseErrorBannerToolButton,
		&QToolButton::clicked,
		this,
		&SignupPage::CloseErrorBanner);
}

SignupPage::~SignupPage()
{
	delete m_ui;
}

void SignupPage::SetErrorBanner(const int code, const std::string& description)
{
	m_ui->ErrorWidget->setVisible(true);
	m_ui->ErrorTitleLabel->setVisible(true);
	m_ui->ErrorCodeLabel->setText(QString::number(code));
	m_ui->ErrorDescriptionLabel->setText(QString::fromStdString(description));
}

void SignupPage::SetErrorBanner(const std::string& description)
{
	m_ui->ErrorWidget->setVisible(true);
	m_ui->ErrorTitleLabel->setVisible(false);
	m_ui->ErrorCodeLabel->setText("");
	m_ui->ErrorDescriptionLabel->setText(QString::fromStdString(description));
}

void SignupPage::CloseErrorBanner()
{
	m_ui->ErrorWidget->setVisible(false);
}

void SignupPage::OnSignupSubmitButtonClicked()
{
	SignupModel::SignupInDTO dto;
	dto.email = m_ui->usernameLineEdit->text().toStdString();
	dto.password = m_ui->passwordCreateLineEdit->text().toStdString();
	dto.pass_repeat = m_ui->passwordRepeatLineEdit->text().toStdString();
	emit Signup(dto);
}
