#include "CategoryEditPage.h"
#include "ui_CategoryEditPage.h"

CategoryEditPage::CategoryEditPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CategoryEditPage)
{
	ui->setupUi(this);
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategorySaveButton->setVisible(false);
}

CategoryEditPage::~CategoryEditPage()
{
	delete ui;
}
