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

    ui->stackedWidget->insertWidget(PageToInt(UIPages::LOGIN), &m_login_page);
    ui->stackedWidget->insertWidget(PageToInt(UIPages::SIGNUP), &m_signup_page);
    ui->stackedWidget->insertWidget(PageToInt(UIPages::HOME), &m_home_page);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetCurrentPage(UIPages page)
{
	ui->stackedWidget->setCurrentIndex(PageToInt(page));
}
