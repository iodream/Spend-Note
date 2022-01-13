#include "SignupWindow.h"
#include "ui_SignupWindow.h"

SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
}

SignupWindow::~SignupWindow()
{
    delete ui;
}
