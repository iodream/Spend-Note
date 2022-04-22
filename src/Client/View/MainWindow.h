#pragma once

#include <QMainWindow>

#include "LoginPage/LoginPage.h"
#include "SignupPage/SignupPage.h"
#include "MainPage/MainPage.h"
#include "Constants.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void SetCurrentPage(UIPages page);
	void changeEvent(QEvent* event);

	LoginPage& get_login_page();
	SignupPage& get_signup_page();
	MainPage& get_main_page();

private:
	static int PageToInt(UIPages page);
	Ui::MainWindow *m_ui;

	LoginPage m_login_page;
	SignupPage m_signup_page;
	MainPage m_main_page;
};
