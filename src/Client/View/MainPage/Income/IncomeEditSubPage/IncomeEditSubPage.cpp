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
	updated_income.amount = ui->Amount->value();
	updated_income.category.id = 1 + ui->Category->currentIndex();
	updated_income.category.name = ui->Category->currentText();
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
	ui->Amount->setValue(income.amount);
	ui->Category->setCurrentText(income.category.name);
//	QDate old_date = QDate::fromString(income.expiration_time);
//	ui->ExpirationDateEdit->setDate(old_date);
}

IncomeEditSubPage::~IncomeEditSubPage()
{
	delete ui;
}

IncomeCategory IncomeEditSubPage::get_category()
{
	IncomeCategory category;

	category.id = 1 + ui->Category->currentIndex();
	category.name = ui->Category->currentText();

	return category;
}


void IncomeEditSubPage::FillCategoryBox(const std::vector<IncomeCategory>& income)
{
	for(const auto& el : income)
	{
		ui->Category->addItem(el.name, el.id);
	}
}
