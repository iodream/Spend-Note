#include "ProductCategoryEditPage.h"
#include "ui_ProductCategoryEditPage.h"

ProductCategoryEditPage::ProductCategoryEditPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ProductCategoryEditPage)
{
	ui->setupUi(this);
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategorySaveButton->setVisible(false);
}

ProductCategoryEditPage::~ProductCategoryEditPage()
{
	delete ui;
}
