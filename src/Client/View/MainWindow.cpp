#include "MainWindow.h"
#include "ui_MainWindow.h"

int MainWindow::PageToInt(UIPages page)
{
	return static_cast<int>(page);
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);

	m_ui->stackedWidget->insertWidget(PageToInt(UIPages::LOGIN), &m_login_page);
	m_ui->stackedWidget->insertWidget(PageToInt(UIPages::SIGNUP), &m_signup_page);
	m_ui->stackedWidget->insertWidget(PageToInt(UIPages::MAIN), &m_main_page);
}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::SetCurrentPage(UIPages page)
{
	m_ui->stackedWidget->setCurrentIndex(PageToInt(page));
}
