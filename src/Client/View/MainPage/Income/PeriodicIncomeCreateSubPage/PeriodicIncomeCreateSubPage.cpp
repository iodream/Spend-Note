#include "PeriodicIncomeCreateSubPage.h"
#include "ui_PeriodicIncomeCreateSubPage.h"

PeriodicIncomeCreateSubPage::PeriodicIncomeCreateSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::PeriodicIncomeCreateSubPage)
{
	m_ui->setupUi(this);

	m_ui->GenerateUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());
	m_ui->GenerateUntil->setDate(QDate::currentDate());

	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
	connect(
		m_ui->SaveButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeCreateSubPage::OnCreateIncome);
	connect(
		m_ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeCreateSubPage::OnNewCategoryPushed);
	connect(
		m_ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeCreateSubPage::OnNewCategorySaved);


}

void PeriodicIncomeCreateSubPage::OnCreateIncome()
{
	Income Income;
	Income.category.name = m_ui->Category->currentText();
	Income.category.id = qvariant_cast<IdType>(m_ui->Category->currentData());
	Income.amount = m_ui->Amount->value();
	Income.name = m_ui->NameLineEdit->text();
	Income.add_time = QDate::currentDate().toString();
	emit CreateIncome(Income);
}

void PeriodicIncomeCreateSubPage::Clear()
{
	m_ui->Amount->clear();
	m_ui->Category->clear();
	m_ui->GenerateUntil->clear();
	m_ui->NameLineEdit->clear();
}

void PeriodicIncomeCreateSubPage::SetMinimumDate(const QDate& date)
{
	m_ui->GenerateUntil->setMinimumDate(date);
}


PeriodicIncomeCreateSubPage::~PeriodicIncomeCreateSubPage()
{
	delete m_ui;
}

void PeriodicIncomeCreateSubPage::FillCategoryBox(const std::vector<IncomeCategory>& Income)
{
	m_ui->Category->clear();
	for(const auto& el : Income)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
}

IncomeCategory PeriodicIncomeCreateSubPage::get_category()
{
	IncomeCategory category;

	category.id = qvariant_cast<IdType>(m_ui->Category->currentData());
	category.name = m_ui->Category->currentText();

	return category;
}

void PeriodicIncomeCreateSubPage::OnNewCategoryPushed()
{
	m_ui->NewCategoryName->setVisible(true);
	m_ui->NewCategorySaveButton->setVisible(true);
	m_ui->NewCategoryButton->setDisabled(true);
}

void PeriodicIncomeCreateSubPage::OnNewCategorySaved()
{
	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
	m_ui->NewCategoryButton->setDisabled(false);
	IncomeCategory category;

	category.id = 0;
	category.name = m_ui->NewCategoryName->text();

	emit AddIncomeCategory(category);
	emit UpdateCategories();
}

