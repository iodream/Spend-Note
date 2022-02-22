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
	m_income.add_time = QDate::currentDate().toString();
	m_income.amount = ui->Amount->value();
	m_income.category.id = qvariant_cast<IdType>(ui->Category->currentData());
	m_income.category.name = ui->Category->currentText();
	m_income.expiration_time = ui->ExpirationDateEdit->date().toString();
	m_income.name = ui->NameLineEdit->text();
	emit UpdateIncome();
}

void IncomeEditSubPage::SetMinimumDate(const QDate& date)
{
	ui->ExpirationDateEdit->setMinimumDate(date);
}

const Income& IncomeEditSubPage::get_income()
{
	return m_income;
}

void IncomeEditSubPage::set_income(const Income& income)
{
	m_income = income;
}

void IncomeEditSubPage::Update(const Income& income)
{
	m_income = income;
	ui->NameLineEdit->setText(income.name);
	ui->Amount->setValue(income.amount);
	ui->Category->setCurrentText(income.category.name);
}

IncomeEditSubPage::~IncomeEditSubPage()
{
	delete ui;
}

IncomeCategory IncomeEditSubPage::get_category()
{
	IncomeCategory category;
	category.id = qvariant_cast<IdType>(ui->Category->currentData());
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
