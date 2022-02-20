#include "DailyListSubPage.h"
#include "ui_DailyListSubPage.h"

DailyListSubPage::DailyListSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DailyListSubPage)
{
	ui->setupUi(this);
}

DailyListSubPage::~DailyListSubPage()
{
	delete ui;
}
