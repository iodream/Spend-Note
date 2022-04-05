#include "CategoryEditPage.h"
#include "ui_CategoryEditPage.h"

CategoryEditPage::CategoryEditPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CategoryEditPage)
{
	ui->setupUi(this);
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategoryEditButton->setVisible(false);
	ui->NewCategoryAddButton->setVisible(false);

	//bottom buttons
	connect(
		ui->EditButton,
		&QPushButton::released,
		this,
		&CategoryEditPage::OnEditCategoryClicked);
	connect(
		ui->AddCategoryButton,
		&QPushButton::released,
		this,
		&CategoryEditPage::OnAddCategoryClicked);
	connect(
		ui->RemoveButton,
		&QPushButton::released,
		this,
		&CategoryEditPage::OnRemoveClicked);

	//small middle buttons
	connect(
		ui->NewCategoryEditButton,
		&QPushButton::released,
		this,
		&CategoryEditPage::OnCategoryEditConfirmClicked);
	connect(
		ui->NewCategoryAddButton,
		&QPushButton::released,
		this,
		&CategoryEditPage::OnCategoryAddConfirmClicked);
}

CategoryEditPage::~CategoryEditPage()
{
	delete ui;
}

void CategoryEditPage::OnEditCategoryClicked()
{
	ui->NewCategoryEdit->setVisible(true);
	ui->NewCategoryEditButton->setVisible(true);
	ui->NewCategoryAddButton->setVisible(false);
}

void CategoryEditPage::OnAddCategoryClicked()
{
	ui->NewCategoryEdit->setVisible(true);
	ui->NewCategoryEditButton->setVisible(false);
	ui->NewCategoryAddButton->setVisible(true);
}

void CategoryEditPage::OnRemoveClicked()
{

}
void CategoryEditPage::OnCategoryEditConfirmClicked()
{
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategoryEditButton->setVisible(false);
}
void CategoryEditPage::OnCategoryAddConfirmClicked()
{
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategoryAddButton->setVisible(false);
}




