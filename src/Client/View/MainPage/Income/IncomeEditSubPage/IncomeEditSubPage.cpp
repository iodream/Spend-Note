#include "IncomeEditSubPage.h"
#include "ui_IncomeEditSubPage.h"

IncomeEditSubPage::IncomeEditSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::IncomeEditSubPage)
{
	ui->setupUi(this);

	ui->ExpirationDateEdit->setDate(QDate::currentDate());
}

IncomeEditSubPage::~IncomeEditSubPage()
{
	delete ui;
}
