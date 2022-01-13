#include "AuthorizedWindow.h"
#include "ui_AuthorizedWindow.h"

AuthorizedWindow::AuthorizedWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorizedWindow)
{
    ui->setupUi(this);
}

AuthorizedWindow::~AuthorizedWindow()
{
    delete ui;
}
