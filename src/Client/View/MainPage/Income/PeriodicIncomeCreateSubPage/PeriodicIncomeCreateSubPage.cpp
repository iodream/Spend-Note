#include "PeriodicIncomeCreateSubPage.h"
#include "ui_PeriodicIncomeCreateSubPage.h"

PeriodicIncomeCreateSubPage::PeriodicIncomeCreateSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PeriodicIncomeCreateSubPage)
{
	ui->setupUi(this);

	ui->GenerateUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());
	ui->GenerateUntil->setDate(QDate::currentDate());

	ui->NewCategoryName->setVisible(false);
	ui->NewCategorySaveButton->setVisible(false);
	connect(
		ui->SaveButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeCreateSubPage::OnCreateIncome);
	connect(
		ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeCreateSubPage::OnNewCategoryPushed);
	connect(
		ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&PeriodicIncomeCreateSubPage::OnNewCategorySaved);


}

void PeriodicIncomeCreateSubPage::OnCreateIncome()
{
	Income Income;
	Income.category.name = ui->Category->currentText();
	Income.category.id = qvariant_cast<IdType>(ui->Category->currentData());
	Income.amount = ui->Amount->value();
	Income.name = ui->NameLineEdit->text();
	Income.add_time = QDate::currentDate().toString();
	emit CreateIncome(Income);
}

void PeriodicIncomeCreateSubPage::Clear()
{
	ui->Amount->clear();
	ui->Category->clear();
	ui->GenerateUntil->clear();
	ui->NameLineEdit->clear();
}

void PeriodicIncomeCreateSubPage::SetMinimumDate(const QDate& date)
{
	ui->GenerateUntil->setMinimumDate(date);
}


PeriodicIncomeCreateSubPage::~PeriodicIncomeCreateSubPage()
{
	delete ui;
}

void PeriodicIncomeCreateSubPage::FillCategoryBox(const std::vector<IncomeCategory>& Income)
{
	ui->Category->clear();
	for(const auto& el : Income)
	{
		ui->Category->addItem(el.name, el.id);
	}
}

IncomeCategory PeriodicIncomeCreateSubPage::get_category()
{
	IncomeCategory category;

	category.id = qvariant_cast<IdType>(ui->Category->currentData());
	category.name = ui->Category->currentText();

	return category;
}

void PeriodicIncomeCreateSubPage::OnNewCategoryPushed()
{
	ui->NewCategoryName->setVisible(true);
	ui->NewCategorySaveButton->setVisible(true);
	ui->NewCategoryButton->setDisabled(true);
}

void PeriodicIncomeCreateSubPage::OnNewCategorySaved()
{
	ui->NewCategoryName->setVisible(false);
	ui->NewCategorySaveButton->setVisible(false);
	ui->NewCategoryButton->setDisabled(false);
	IncomeCategory category;

	category.id = 0;
	category.name = ui->NewCategoryName->text();

	emit AddIncomeCategory(category);
	emit UpdateCategories();
}

