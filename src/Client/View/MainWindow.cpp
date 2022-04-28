#include "MainWindow.h"
#include "ui_MainWindow.h"

LoginPage& MainWindow::get_login_page()
{
	return m_login_page;
}

SignupPage& MainWindow::get_signup_page()
{
	return m_signup_page;
}

MainPage& MainWindow::get_main_page()
{
	return m_main_page;
}

int MainWindow::PageToInt(UIPages page)
{
	return static_cast<int>(page);
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	m_ui->stackedWidget->insertWidget(PageToInt(UIPages::LOGIN), &get_login_page());
	m_ui->stackedWidget->insertWidget(PageToInt(UIPages::SIGNUP), &get_signup_page());
	m_ui->stackedWidget->insertWidget(PageToInt(UIPages::MAIN), &get_main_page());
}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::SetCurrentPage(UIPages page)
{
	m_ui->stackedWidget->setCurrentIndex(PageToInt(page));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	emit SaveConfig();
	event->accept();
}
