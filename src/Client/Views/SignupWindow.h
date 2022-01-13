#pragma once

#include <QWidget>

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();

private:
    Ui::SignupWindow *ui;
};
