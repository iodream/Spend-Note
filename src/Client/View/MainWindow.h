#pragma once

#include <QMainWindow>

#include "LoginPage/LoginPage.h"
#include "SignupPage/SignupPage.h"
#include "HomePage/HomePage.h"
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

    LoginPage loginPage;
    SignupPage signupPage;
    HomePage homePage;

private:
    static int PageToInt(UIPages page);
    Ui::MainWindow *ui;
};
