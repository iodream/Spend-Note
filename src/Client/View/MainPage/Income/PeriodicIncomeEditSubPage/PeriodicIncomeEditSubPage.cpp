#include "PeriodicIncomeEditSubPage.h"
#include "ui_PeriodicIncomeEditSubPage.h"

PeriodicIncomeEditSubPage::PeriodicIncomeEditSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::PeriodicIncomeEditSubPage)
{
	m_ui->setupUi(this);

	m_ui->GenerateUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());

	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);

	connect(
		m_ui->SubmitButton,
		&QPushButton::clicked,
		this,
		&PeriodicIncomeEditSubPage::OnEditIncome);
	connect(
		m_ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeEditSubPage::OnNewCategoryPushed);
	connect(
		m_ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeEditSubPage::OnNewCategorySaved);

}


void PeriodicIncomeEditSubPage::OnEditIncome()
{
	m_income.add_time = QDate::currentDate().toString();
	m_income.amount = m_ui->Amount->value();
	m_income.category.id = qvariant_cast<IdType>(m_ui->Category->currentData());
	m_income.category.name = m_ui->Category->currentText();
	m_income.expiration_time = m_ui->GenerateUntil->date().toString();
	m_income.name = m_ui->NameLineEdit->text();
	emit UpdateIncome();
}

void PeriodicIncomeEditSubPage::SetMinimumDate(const QDate& date)
{
	m_ui->GenerateUntil->setMinimumDate(date);
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
	m_ui->NameLineEdit->setText(income.name);
	m_ui->Amount->setValue(income.amount);
	m_ui->Category->setCurrentText(income.category.name);
}

PeriodicIncomeEditSubPage::~PeriodicIncomeEditSubPage()
{
	delete m_ui;
}

IncomeCategory PeriodicIncomeEditSubPage::get_category()
{
	IncomeCategory category;
	category.id = qvariant_cast<IdType>(m_ui->Category->currentData());
	category.name = m_ui->Category->currentText();
	return category;
}


void PeriodicIncomeEditSubPage::FillCategoryBox(const std::vector<IncomeCategory>& income)
{
	m_ui->Category->clear();
	for(const auto& el : income)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
}

void PeriodicIncomeEditSubPage::OnNewCategoryPushed()
{
	m_ui->NewCategoryName->setVisible(true);
	m_ui->NewCategorySaveButton->setVisible(true);
	m_ui->NewCategoryButton->setDisabled(true);
}

void PeriodicIncomeEditSubPage::OnNewCategorySaved()
{
	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
	m_ui->NewCategoryButton->setDisabled(false);

	IncomeCategory cat;

	cat.id = 0;
	cat.name = m_ui->NewCategoryName->text();

	emit AddIncomeCategory(cat);
	emit UpdateCategories();

}

