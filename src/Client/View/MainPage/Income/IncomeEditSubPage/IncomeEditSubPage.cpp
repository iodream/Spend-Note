#include "IncomeEditSubPage.h"
#include "ui_IncomeEditSubPage.h"
IncomeEditSubPage::IncomeEditSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::IncomeEditSubPage)
{
	ui->setupUi(this);

	ui->ExpirationDateEdit->setDate(QDate::currentDate());
	
	connect(
		ui->SubmitButton,
		&QPushButton::clicked,
		this,
		&IncomeEditSubPage::OnEditIncome);
}


void IncomeEditSubPage::OnEditIncome()
{
	Income updated_income;
	updated_income.add_time = QDate::currentDate().toString();
	updated_income.amount = ui->AmountLineEdit->text().toLongLong();
	updated_income.category.id = 1;
	updated_income.category.name = ui->CategoryLineEdit->text();
	updated_income.expiration_time = ui->ExpirationDateEdit->date().toString();
	updated_income.name = ui->NameLineEdit->text();
	emit UpdateIncome(updated_income);	
}

void IncomeEditSubPage::SetMinimumDate(const QDate& date)
{
	ui->ExpirationDateEdit->setMinimumDate(date);
}

void IncomeEditSubPage::Update(const Income& income)
{
	ui->NameLineEdit->setText(income.name);
	ui->AmountLineEdit->setText(QString::number(income.amount));
	ui->CategoryLineEdit->setText(income.category.name);
//	QDate old_date = QDate::fromString(income.expiration_time);
//	ui->ExpirationDateEdit->setDate(old_date);
}

IncomeEditSubPage::~IncomeEditSubPage()
{
	delete ui;
}
