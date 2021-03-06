#include "CategoryEditPage.h"
#include "ui_CategoryEditPage.h"

#include "View/MainPage/MainPage.h"
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

void CategoryEditPage::changeEvent(QEvent* event)
{
	if(event)
	{
		switch(event->type())
		{
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		}

		QWidget::changeEvent(event);
	}
}

void CategoryEditPage::Update(const std::vector<ProductCategory>& categories)
{
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategoryEditButton->setVisible(false);
	ui->NewCategoryAddButton->setVisible(false);

	ui->Products->clear();
	for(auto it:categories)
	{
		QListWidgetItem *newItem = new QListWidgetItem;
		QString name(it.name);
		QVariant data(it.id);
		newItem->setText(name);
		newItem->setData(Qt::UserRole, data);
		ui->Products->addItem(newItem);
	}
}

void CategoryEditPage::Update(const std::vector<IncomeCategory>& categories)
{
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategoryEditButton->setVisible(false);
	ui->NewCategoryAddButton->setVisible(false);

	ui->Incomes->clear();
	for(auto it:categories)
	{
		QListWidgetItem *newItem = new QListWidgetItem;
		QString name(it.name);
		QVariant data(it.id);
		newItem->setText(name);
		newItem->setData(Qt::UserRole, data);
		ui->Incomes->addItem(newItem);
	}
}

void CategoryEditPage::OnEditCategoryClicked() // shows fields for editing
{
	ui->NewCategoryEdit->clear();
	ui->NewCategoryEdit->setVisible(true);
	ui->NewCategoryEditButton->setVisible(true);
	ui->NewCategoryAddButton->setVisible(false);
}

void CategoryEditPage::OnAddCategoryClicked() // shows fields for adding
{
	ui->NewCategoryEdit->clear();
	ui->NewCategoryEdit->setVisible(true);
	ui->NewCategoryEditButton->setVisible(false);
	ui->NewCategoryAddButton->setVisible(true);
}

void CategoryEditPage::UpdateColors()
{
	ui->label->setStyleSheet("background-color:" + QString(MainPage::ColorSettings::COLOR_TOP_BANNER));
}

void CategoryEditPage::OnRemoveClicked()
{
	if(ui->tabWidget->currentIndex() == 0)
	{
		if(ui->Incomes->currentRow() == -1) // if user didn't select a category
		{
			emit ClientError(tr("Please Select an item!"));
			return;
		}
		int id = qvariant_cast<int>(ui->Incomes->currentItem()->data(Qt::UserRole));
		IncomeCategoryId id_removed {id};
		emit RemoveIncomeCategory(id_removed);
	}
	else
	{
		if(ui->Products->currentRow() == -1)
		{
			emit ClientError(tr("Please Select an item!"));
			return;
		}
		int id = qvariant_cast<int>(ui->Products->currentItem()->data(Qt::UserRole));
		ProductCategoryId id_removed {id};
		emit RemoveProductCategory(id_removed);
	}
}
void CategoryEditPage::OnCategoryEditConfirmClicked()
{
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategoryEditButton->setVisible(false);

	if(ui->tabWidget->currentIndex() == 0) // see if we're on incomes tab
		{
			if(ui->Incomes->currentRow() == -1) // if user didn't select a category
			{
				emit ClientError(tr("Please Select an item!"));
				return;
			}
			IncomeCategory cat;
			auto Item = ui->Incomes->currentItem();
			cat.id = qvariant_cast<int>(Item->data(Qt::UserRole));
			cat.name = ui->NewCategoryEdit->text();

			emit UpdateIncomeCategory(cat);
		}
	else // or on products tab
	{
		if(ui->Products->currentRow() == -1)
		{
			emit ClientError(tr("Please Select an item!"));
			return;
		}
		ProductCategory cat;
		auto Item = ui->Products->currentItem();
		cat.id = qvariant_cast<int>(Item->data(Qt::UserRole));

		cat.name = ui->NewCategoryEdit->text();

		emit UpdateProductCategory(cat);
	}
}
void CategoryEditPage::OnCategoryAddConfirmClicked()
{
	ui->NewCategoryEdit->setVisible(false);
	ui->NewCategoryAddButton->setVisible(false);

	if(ui->tabWidget->currentIndex() == 0)
		{
			IncomeCategory cat;

			cat.id = 0;
			cat.name = ui->NewCategoryEdit->text();

			emit AddIncomeCategory(cat);
		}
	else
	{
		ProductCategory cat;

		cat.id = 0;
		cat.name = ui->NewCategoryEdit->text();
		emit AddProductCategory(cat);
	}
}
