#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(&loginWindow);
    ui->stackedWidget->addWidget(&signupWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_signupButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}
