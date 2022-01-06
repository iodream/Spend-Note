#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginSubmitButton_clicked()
{
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();


    ui->statusbar->showMessage("Authorization is in process");

    // encrypting password(hardcoded now);
    QString encryptedPassword = password;


    // creating a .json file with login and password in it
    QJsonObject loginObject;
    loginObject.insert("login", login);
    loginObject.insert("password", encryptedPassword);
    QJsonDocument json(loginObject);

    qDebug() << json;

    // sending request to server with this .json file
    // checking whether the input is ok
    // receiving response

    ui->statusbar->showMessage("Authorization completed");
}

void MainWindow::on_signupButton_clicked()
{
    // moving to signup page
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_signupSubmitButton_clicked()
{
    // checking whether the passwords input are the same (it may be done on server, but i implemented that here)
    // else creating a .json with email, username and password
    if(ui->passwordCreateLineEdit->text() != ui->passwordRepeatLineEdit->text())
    {
        ui->statusbar->showMessage("Sign up failed(passwords do not match)");
    }
    else
    {
        QString email = ui->emailLineEdit->text();
        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordCreateLineEdit->text();

        // encrypting password(hardcoded now)
        QString encryptedPassword = password;

        QJsonObject signupObject;
        signupObject.insert("email", email);
        signupObject.insert("username", username);
        signupObject.insert("password", encryptedPassword);

        QJsonDocument json(signupObject);

        qDebug() << json;

        // sending request to server with this .json file
        // checking whether the input is ok, handling all possible situations
        // receiving response

        ui->statusbar->showMessage("Sign up succeeded");
        ui->stackedWidget->setCurrentIndex(0);
    }
}
