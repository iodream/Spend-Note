#include "LoginPage.h"
#include "ui_LoginPage.h"

#include "iostream"

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);

}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::ChangeLoginErrorLabel(std::string reason)
{
    ui->loginErrorLabel->setText(QString::fromStdString(reason));
}

void LoginPage::on_loginSubmitButton_clicked()
{
    LoginInDTO loginInDTO;
    loginInDTO.login = ui->loginLineEdit->text().toStdString();
    loginInDTO.password = ui->passwordLineEdit->text().toStdString();;
    emit Login(loginInDTO);
}

