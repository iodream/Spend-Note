#pragma once

#include <QMainWindow>

#include "LoginWindow.h"
#include "SignupWindow.h"
#include "AuthorizedWindow.h"
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

private:
    Ui::MainWindow *ui;
    LoginWindow loginWindow;
    SignupWindow signupWindow;
    AuthorizedWindow authorizedWindow;

private slots:
    void on_loginButton_clicked();
    void on_signupButton_clicked();
    void on_stackedWidget_currentChanged(int arg1);
};
