#include "IncomeEditSubPage.h"
#include "ui_IncomeEditSubPage.h"

IncomeEditSubPage::IncomeEditSubPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::IncomeEditSubPage)
{
	ui->setupUi(this);

	ui->ExpirationDateEdit->setDate(QDate::currentDate());
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
