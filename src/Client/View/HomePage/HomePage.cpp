#include "HomePage.h"
#include "ui_HomePage.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
	m_ui(new Ui::HomePage)
{
	m_ui->setupUi(this);
}

HomePage::~HomePage()
{
	delete m_ui;
}
