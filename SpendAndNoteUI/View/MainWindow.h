#pragma once

#include <QMainWindow>
#include <QMessageBox>

#include "./Constants.h"
#include "./Controller/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void OnLogin(LoginInDTO loginInDTO);

private slots:
    void on_signupButton_clicked();

    void on_loginSubmitButton_clicked();

    void on_signupSubmitButton_clicked();

    void mousePressed(UIAuthorizedPages page);

public slots:
    void OnSuccessLogin(UIPages);
    void OnUnsuccessLogin(std::string);

public:
    Ui::MainWindow *ui;
};

