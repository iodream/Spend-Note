#include "IncomeCreateSubPage.h"
#include "ui_IncomeCreateSubPage.h"

IncomeCreateSubPage::IncomeCreateSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::IncomeCreateSubPage)
{
	ui->setupUi(this);

	ui->ExpirationDateEdit->setDate(QDate::currentDate());
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

	category.id = qvariant_cast<IdType>(ui->Category->currentData());
	category.name = ui->Category->currentText();

	return category;
}
