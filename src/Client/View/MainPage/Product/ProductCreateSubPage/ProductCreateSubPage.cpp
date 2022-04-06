#include "ProductCreateSubPage.h"
#include "ui_ProductCreateSubPage.h"

ProductCreateSubPage::ProductCreateSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductCreateSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		this,
		&ProductCreateSubPage::CreateProduct);

	m_ui->BuyUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());

	m_ui->BuyUntil->setDate(QDate::currentDate());
	SetMinimumDate(QDate::currentDate());

	connect(
		m_ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&ProductCreateSubPage::OnNewCategoryPushed);
	connect(
		m_ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&ProductCreateSubPage::OnNewCategorySaved);

	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
}

ProductCreateSubPage::~ProductCreateSubPage()
{
	delete m_ui;
}

QString ProductCreateSubPage::GetName()
{
	return m_ui->Name->text();
}

Money ProductCreateSubPage::GetPrice()
{
	return m_ui->Price->value();
}

BigInt ProductCreateSubPage::GetAmount()
{
	return m_ui->Amount->value();
}

bool ProductCreateSubPage::GetIsBought()
{
	return m_ui->IsBought->isChecked();
}

QString ProductCreateSubPage::GetBuyUntil()
{
	return toDBstring(m_ui->BuyUntil->dateTime());
}

BigInt ProductCreateSubPage::GetPriority()
{
	return m_ui->Priority->value();
}

IdType ProductCreateSubPage::GetCategoryId()
{
	return qvariant_cast<IdType>(m_ui->Category->currentData());
}

QString ProductCreateSubPage::GetCategoryName()
{
	return m_ui->Category->currentText();
}

void ProductCreateSubPage::Clear()
{
	m_ui->Name->clear();
	m_ui->Price->clear();
	m_ui->Amount->clear();
	m_ui->Priority->clear();
	m_ui->BuyUntil->clear();
	m_ui->Name->clear();
	m_ui->IsBought->setChecked(false);
}

void ProductCreateSubPage::FillCategoryBox(const std::vector<ProductCategory> &categories)
{
	m_ui->Category->clear();
	for(const auto& el : categories)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
}

void ProductCreateSubPage::SetRangeOfSpinBox()
{
	m_ui->Amount->setRange(1, 100); // need to be changed do not hardcode
	m_ui->Priority->setRange(1, 5);
}

void ProductCreateSubPage::SetMinimumDate(const QDate& date)
{
	m_ui->BuyUntil->setMinimumDate(date);
}

void ProductCreateSubPage::OnNewCategoryPushed()
{
	m_ui->NewCategoryName->setVisible(true);
	m_ui->NewCategorySaveButton->setVisible(true);
	m_ui->NewCategoryButton->setDisabled(true);
}

void ProductCreateSubPage::OnNewCategorySaved()
{
	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
	m_ui->NewCategoryButton->setDisabled(false);

	ProductCategory cat;

	cat.id = 0;
	cat.name = m_ui->NewCategoryName->text();

	emit AddProductCategory(cat);
	emit UpdateCategories();
}
