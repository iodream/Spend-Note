#pragma once

#include <QWidget>

#include "DTO/Login.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

signals:
    void Login(LoginInDTO);

private slots:
    void on_loginSubmitButton_clicked();

private:
    Ui::LoginPage *ui;
};

