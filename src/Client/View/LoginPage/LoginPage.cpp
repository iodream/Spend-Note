#include "LoginPage.h"
#include "ui_LoginPage.h"

LoginPage::LoginPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::LoginPage)
{
	m_ui->setupUi(this);

	connect(m_ui->loginSubmitButton, SIGNAL(clicked())
			, this, SLOT(OnLoginSubmitButtonClicked()));
}

LoginPage::~LoginPage()
{
	delete m_ui;
}

void LoginPage::ChangeLoginErrorLabel(std::string reason)
{
	m_ui->loginErrorLabel->setText(QString::fromStdString(reason));
}

void LoginPage::OnLoginSubmitButtonClicked()
{
	LoginInDTO login_in_dto;
	login_in_dto.login = m_ui->loginLineEdit->text().toStdString();
	login_in_dto.password = m_ui->passwordLineEdit->text().toStdString();
	emit Login(login_in_dto);
}


void LoginPage::on_signupButton_clicked()
{
	emit GotoSignup();
}

void LoginPage::on_passwordLineEdit_textChanged(const QString& arg1)
{
	m_ui->loginErrorLabel->setText("");
}

void LoginPage::on_loginLineEdit_textChanged(const QString& arg1)
{
	m_ui->loginErrorLabel->setText("");
}

