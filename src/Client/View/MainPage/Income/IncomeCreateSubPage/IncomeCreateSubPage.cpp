#include "IncomeCreateSubPage.h"
#include "ui_IncomeCreateSubPage.h"

IncomeCreateSubPage::IncomeCreateSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::IncomeCreateSubPage)
{
	ui->setupUi(this);
}

IncomeCreateSubPage::~IncomeCreateSubPage()
{
	delete ui;
}
