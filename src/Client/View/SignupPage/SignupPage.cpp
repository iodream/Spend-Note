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
