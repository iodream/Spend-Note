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

void IncomeCreateSubPage::Clear()
{
	ui->AmountLineEdit->clear();
	ui->CategoryLineEdit->clear();
	ui->ExpirationDateEdit->clear();
	ui->NameLineEdit->clear();
}

void IncomeCreateSubPage::SetMinimumDate(const QDate& date)
{
	ui->ExpirationDateEdit->setMinimumDate(date);
}


IncomeCreateSubPage::~IncomeCreateSubPage()
{
	delete ui;
}

void IncomeCreateSubPage::FillCategoryBox(const std::vector<IncomeCategory>& income)
{
	for(const auto& el : income)
	{
		ui->Category->addItem(el.name, el.id);
	}
}

IncomeCategory IncomeCreateSubPage::get_category()
{
	IncomeCategory category;

	category.id = 1 + ui->Category->currentIndex();
	category.name = ui->Category->currentText();

	return category;
}
