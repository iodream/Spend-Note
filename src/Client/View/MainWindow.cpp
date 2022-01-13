#include "MainWindow.h"
#include "ui_MainWindow.h"

int MainWindow::PageToInt(UIPages page)
{
	return static_cast<int>(page);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->insertWidget(PageToInt(UIPages::LOGIN), &loginPage);
    ui->stackedWidget->insertWidget(PageToInt(UIPages::SIGNUP), &signupPage);
    ui->stackedWidget->insertWidget(PageToInt(UIPages::HOME), &homePage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnCurrentPageChange(UIPages page)
{
	ui->stackedWidget->setCurrentIndex(PageToInt(page));
}
