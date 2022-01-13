#pragma once

#include <QWidget>

namespace Ui {
class SignupPage;
}

class SignupPage : public QWidget
{
    Q_OBJECT

public:
    explicit SignupPage(QWidget *parent = nullptr);
    ~SignupPage();

private:
    Ui::SignupPage *ui;
};
