#include "IncomeCreateSubPage.h"
#include "ui_IncomeCreateSubPage.h"

IncomeCreateSubPage::IncomeCreateSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::IncomeCreateSubPage)
{
	ui->setupUi(this);

	ui->ExpirationDateEdit->setDisplayFormat(
		QLocale::system().dateTimeFormat());
	ui->ExpirationDateEdit->setDate(QDate::currentDate());

	ui->NewCategoryName->setVisible(false);
	ui->NewCategorySaveButton->setVisible(false);
	connect(
		ui->SaveButton,
		&QPushButton::released,
		this,
		&IncomeCreateSubPage::OnCreateIncome);
	connect(
		ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&IncomeCreateSubPage::OnNewCategoryPushed);
	connect(
		ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&IncomeCreateSubPage::OnNewCategorySaved);


}

void IncomeCreateSubPage::OnCreateIncome()
{
	Income income;
	income.category.name = ui->Category->currentText();
	income.category.id = qvariant_cast<IdType>(ui->Category->currentData());
	income.amount = ui->Amount->value();
	income.name = ui->NameLineEdit->text();
	income.add_time = QDate::currentDate().toString();
	income.expiration_time = ui->ExpirationDateEdit->date().toString();
	emit CreateIncome(income);
}

void IncomeCreateSubPage::Clear()
{
	ui->Amount->clear();
	ui->Category->clear();
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
	ui->Category->clear();
	for(const auto& el : income)
	{
		ui->Category->addItem(el.name, el.id);
	}
}

IncomeCategory IncomeCreateSubPage::get_category()
{
	IncomeCategory category;

	category.id = qvariant_cast<IdType>(ui->Category->currentData());
	category.name = ui->Category->currentText();

	return category;
}

void IncomeCreateSubPage::OnNewCategoryPushed()
{
	ui->NewCategoryName->setVisible(true);
	ui->NewCategorySaveButton->setVisible(true);
	ui->NewCategoryButton->setDisabled(true);
}

void IncomeCreateSubPage::OnNewCategorySaved()
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

