#include "PeriodicIncomeEditSubPage.h"
#include "ui_PeriodicIncomeEditSubPage.h"

PeriodicIncomeEditSubPage::PeriodicIncomeEditSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PeriodicIncomeEditSubPage)
{
	ui->setupUi(this);

	ui->GenerateUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());

	ui->NewCategoryName->setVisible(false);
	ui->NewCategorySaveButton->setVisible(false);

	connect(
		ui->SubmitButton,
		&QPushButton::clicked,
		this,
		&PeriodicIncomeEditSubPage::OnEditIncome);
	connect(
		ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeEditSubPage::OnNewCategoryPushed);
	connect(
		ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeEditSubPage::OnNewCategorySaved);

}


void PeriodicIncomeEditSubPage::OnEditIncome()
{
	m_income.add_time = QDate::currentDate().toString();
	m_income.amount = ui->Amount->value();
	m_income.category.id = qvariant_cast<IdType>(ui->Category->currentData());
	m_income.category.name = ui->Category->currentText();
	m_income.expiration_time = ui->GenerateUntil->date().toString();
	m_income.name = ui->NameLineEdit->text();
	emit UpdateIncome();
}

void PeriodicIncomeEditSubPage::SetMinimumDate(const QDate& date)
{
	ui->GenerateUntil->setMinimumDate(date);
}

const Income& PeriodicIncomeEditSubPage::get_income()
{
	return m_income;
}

void PeriodicIncomeEditSubPage::set_income(const Income& income)
{
	m_income = income;
}

void PeriodicIncomeEditSubPage::Update(const Income& income)
{
	m_income = income;
	ui->NameLineEdit->setText(income.name);
	ui->Amount->setValue(income.amount);
	ui->Category->setCurrentText(income.category.name);
}

PeriodicIncomeEditSubPage::~PeriodicIncomeEditSubPage()
{
	delete ui;
}

IncomeCategory PeriodicIncomeEditSubPage::get_category()
{
	IncomeCategory category;
	category.id = qvariant_cast<IdType>(ui->Category->currentData());
	category.name = ui->Category->currentText();
	return category;
}


void PeriodicIncomeEditSubPage::FillCategoryBox(const std::vector<IncomeCategory>& income)
{
	ui->Category->clear();
	for(const auto& el : income)
	{
		ui->Category->addItem(el.name, el.id);
	}
}

void PeriodicIncomeEditSubPage::OnNewCategoryPushed()
{
	ui->NewCategoryName->setVisible(true);
	ui->NewCategorySaveButton->setVisible(true);
	ui->NewCategoryButton->setDisabled(true);
}

void PeriodicIncomeEditSubPage::OnNewCategorySaved()
{
	ui->NewCategoryName->setVisible(false);
	ui->NewCategorySaveButton->setVisible(false);
	ui->NewCategoryButton->setDisabled(false);

	IncomeCategory cat;

	cat.id = 0;
	cat.name = ui->NewCategoryName->text();

	emit AddIncomeCategory(cat);
	emit UpdateCategories();

}

