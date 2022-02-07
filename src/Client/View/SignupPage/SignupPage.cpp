#include "SignupPage.h"
#include "ui_SignupPage.h"

SignupPage::SignupPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::SignupPage)
{
	m_ui->setupUi(this);
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
}

SignupPage::~SignupPage()
{
	delete m_ui;
}

void SignupPage::OnSignupSubmitButtonClicked()
{
	SignupModel::SignupInDTO dto;
	dto.login = m_ui->usernameLineEdit->text().toStdString();
	dto.password = m_ui->passwordCreateLineEdit->text().toStdString();
	dto.pass_repeat = m_ui->passwordRepeatLineEdit->text().toStdString();
	emit Signup(dto);
}
