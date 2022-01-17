#include "LoginPage.h"
#include "ui_LoginPage.h"

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    connect(ui->loginSubmitButton, SIGNAL(clicked())
            , this, SLOT(OnLoginSubmitButtonClicked()));
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::ChangeLoginErrorLabel(std::string reason)
{
    ui->loginErrorLabel->setText(QString::fromStdString(reason));
}

void LoginPage::OnLoginSubmitButtonClicked()
{
    LoginInDTO login_in_dto;
    login_in_dto.login = ui->loginLineEdit->text().toStdString();
    login_in_dto.password = ui->passwordLineEdit->text().toStdString();
    emit Login(login_in_dto);
}

