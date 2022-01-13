#pragma once


#include <QWidget>

namespace Ui {
class AuthorizedWindow;
}

class AuthorizedWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizedWindow(QWidget *parent = nullptr);
    ~AuthorizedWindow();

private:
    Ui::AuthorizedWindow *ui;
};
