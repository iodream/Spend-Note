#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "./DTO/Login.h"

#include "./ClickableLabel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainTab->page = UIAuthorizedPages::MAIN;
    connect(ui->mainTab, &ClickableLabel::MousePressed, this, &MainWindow::mousePressed);

    ui->settingsTab->page = UIAuthorizedPages::SETTINGS;
    connect(ui->settingsTab, &ClickableLabel::MousePressed, this, &MainWindow::mousePressed);

    ui->manageBalanceTab->page = UIAuthorizedPages::MANAGE_BALANCE;
    connect(ui->manageBalanceTab, &ClickableLabel::MousePressed, this, &MainWindow::mousePressed);

    ui->getReportTab->page = UIAuthorizedPages::GET_REPORT;
    connect(ui->getReportTab, &ClickableLabel::MousePressed, this, &MainWindow::mousePressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginSubmitButton_clicked()
{
    ui->unsuccessfulLoginLabel->setText("");

    LoginInDTO loginInDTO;
    QString qLogin = ui->loginLineEdit->text();
    QString qPassword = ui->passwordLineEdit->text();

    loginInDTO.login = qLogin.toStdString();
    loginInDTO.password = qPassword.toStdString();

    Controller controller;

    connect(&controller, &Controller::OnSuccessLogin, this, &MainWindow::OnSuccessLogin);
    connect(&controller, &Controller::OnUnsuccessLogin, this, &MainWindow::OnUnsuccessLogin);

    connect(this, &MainWindow::OnLogin, &controller, &Controller::OnLogin);
    emit OnLogin(loginInDTO);
}

void MainWindow::on_signupButton_clicked()
{
    // moving to signup page
    ui->stackedWidget->setCurrentIndex(static_cast<int>(UIPages::SIGNUP));
}

void MainWindow::on_signupSubmitButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(static_cast<int>(UIPages::LOGIN));
}

void MainWindow::OnSuccessLogin(UIPages page)
{
    ui->stackedWidget->setCurrentIndex(static_cast<int>(page));
}

void MainWindow::OnUnsuccessLogin(std::string reason)
{
    ui->unsuccessfulLoginLabel->setText(QString::fromStdString(reason));
}


void MainWindow::mousePressed(UIAuthorizedPages page)
{
    ui->mainPageStackedWidget->setCurrentIndex(static_cast<int>(page));
}
