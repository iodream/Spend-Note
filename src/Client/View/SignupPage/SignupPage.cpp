#include "SignupPage.h"
#include "ui_SignupPage.h"

SignupPage::SignupPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::SignupPage)
{
	m_ui->setupUi(this);
}

SignupPage::~SignupPage()
{
	delete m_ui;
}

void SignupPage::on_signupSubmitButton_clicked()
{
	SignupModel::SignupInDTO dto;
	dto.login = m_ui->usernameLineEdit->text().toStdString();
	dto.password = m_ui->passwordCreateLineEdit->text().toStdString();
	dto.pass_repeat = m_ui->passwordRepeatLineEdit->text().toStdString();
	emit Signup(dto);
}

void SignupPage::on_GoBackButton_clicked()
{
	emit GotoLoginPage();
}

