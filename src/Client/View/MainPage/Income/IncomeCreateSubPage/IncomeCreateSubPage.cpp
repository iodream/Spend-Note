#include "IncomeCreateSubPage.h"
#include "ui_IncomeCreateSubPage.h"

IncomeCreateSubPage::IncomeCreateSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::IncomeCreateSubPage)
{
	ui->setupUi(this);

	ui->ExpirationDateEdit->setDate(QDate::currentDate());
	connect(
		ui->SaveButton,
		&QPushButton::released,
		this,
		&IncomeCreateSubPage::OnCreateIncome);
}

void IncomeCreateSubPage::OnCreateIncome()
{
	Income income;
	income.category.name = ui->CategoryLineEdit->text();
	income.category.id = 1;
	income.amount = ui->AmountLineEdit->text().toLongLong();
	income.name = ui->NameLineEdit->text();
	income.add_time = QDate::currentDate().toString();
	income.expiration_time = ui->ExpirationDateEdit->text();
	emit CreateIncome(income);
}
IncomeCreateSubPage::~IncomeCreateSubPage()
{
	delete ui;
}
