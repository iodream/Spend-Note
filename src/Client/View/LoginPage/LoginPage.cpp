#include "LoginPage.h"
#include "ui_LoginPage.h"

LoginPage::LoginPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::LoginPage)
{
	m_ui->setupUi(this);

	m_ui->ErrorWidget->setVisible(false); // making our banner invisible

	connect(
		m_ui->loginSubmitButton,
		SIGNAL(clicked()),
		this,
		SLOT(OnLoginSubmitButtonClicked()));

	connect(
		m_ui->signupButton,
		SIGNAL(clicked()),
		this,
		SLOT(OnSignupButtonClicked()));

	connect(
		m_ui->loginLineEdit,
		SIGNAL(textChanged(QString)),
		this,
		SLOT(OnLoginTextChanged(QString)));

	connect(
		m_ui->passwordLineEdit,
		SIGNAL(textChanged(QString)),
		this,
		SLOT(OnPasswordTextChanged(QString)));

	connect(
		m_ui->CloseErrorBannerToolButton,
		&QToolButton::clicked,
		this,
		&LoginPage::CloseErrorBanner);

	connect(
		m_ui->showPassword,
		&QCheckBox::clicked,
		this,
		&LoginPage::OnShowPasswordClick);
}

LoginPage::~LoginPage()
{
	delete m_ui;
}

void LoginPage::ChangeLoginErrorLabel(std::string reason)
{
	m_ui->loginErrorLabel->setText(QString::fromStdString(reason));
}

void LoginPage::SetErrorBanner(const int code, const std::string& description)
{
	m_ui->ErrorWidget->setVisible(true);
	m_ui->ErrorTitleLabel->setVisible(true);
	m_ui->ErrorCodeLabel->setText(QString::number(code));
	m_ui->ErrorDescriptionLabel->setText(QString::fromStdString(description));
}

void LoginPage::SetErrorBanner(const std::string& description)
{
	m_ui->ErrorWidget->setVisible(true);
	m_ui->ErrorTitleLabel->setVisible(false);
	m_ui->ErrorCodeLabel->setText("");
	m_ui->ErrorDescriptionLabel->setText(QString::fromStdString(description));
}

void LoginPage::CloseErrorBanner()
{
	m_ui->ErrorWidget->setVisible(false);
}

void LoginPage::OnLoginSubmitButtonClicked()
{
	LoginModel::JSONFormatter::Credentials credentials;
	credentials.login = m_ui->loginLineEdit->text().toStdString();
	credentials.password = m_ui->passwordLineEdit->text().toStdString();
	emit Login(credentials);
}

void LoginPage::OnSignupButtonClicked()
{
	emit GotoSignup();
}

void LoginPage::OnLoginTextChanged(const QString& arg1)
{
	m_ui->loginErrorLabel->setText("");
}

void LoginPage::OnPasswordTextChanged(const QString& arg1)
{
	m_ui->loginErrorLabel->setText("");
}

void LoginPage::OnShowPasswordClick()
{
	if(m_ui->showPassword->isChecked()){
		m_ui->passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
	}
	else
	{
		m_ui->passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
	}
}

