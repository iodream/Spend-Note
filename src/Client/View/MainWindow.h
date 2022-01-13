#pragma once

#include <QMainWindow>

#include "LoginPage/LoginPage.h"
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

	static int PageToInt(UIPages page);

private:
    Ui::MainWindow *ui;
    LoginPage loginPage;

private slots:
	void OnCurrentPageChange(UIPages page);
};
