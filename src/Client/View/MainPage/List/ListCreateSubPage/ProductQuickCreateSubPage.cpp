#include "ProductQuickCreateSubPage.h"
#include "ui_ProductQuickCreateSubPage.h"

ProductQuickCreateSubPage::ProductQuickCreateSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductQuickCreateSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		this,
		&ProductQuickCreateSubPage::QuickAddItem);

	m_ui->BuyUntil->setDate(QDate::currentDate());
	SetMinimumDate(QDate::currentDate());
}

ProductQuickCreateSubPage::~ProductQuickCreateSubPage()
{
	delete m_ui;
}

QString ProductQuickCreateSubPage::GetName()
{
	return m_ui->Name->text();
}

Money ProductQuickCreateSubPage::GetPrice()
{
	return m_ui->Price->text().toLongLong();
}

BigInt ProductQuickCreateSubPage::GetAmount()
{
	return m_ui->Amount->value();
}

bool ProductQuickCreateSubPage::GetIsBought()
{
	return m_ui->IsBought->isChecked();
}

QString ProductQuickCreateSubPage::GetBuyUntil()
{
	return toDBstring(m_ui->BuyUntil->dateTime());
}

BigInt ProductQuickCreateSubPage::GetPriority()
{
	return m_ui->Priority->value();
}

QString ProductQuickCreateSubPage::GetCategoryName()
{
	return m_ui->Category->currentText();
}

IdType ProductQuickCreateSubPage::GetCategoryId()
{
	return m_ui->Category->currentIndex() + 1;
}

void ProductQuickCreateSubPage::FillCategoryBox(const std::vector<ProductCategory> &categories)
{
	for(const auto& el : categories)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
}

void ProductQuickCreateSubPage::Clear()
{
	m_ui->Name->clear();
	m_ui->Price->clear();
	m_ui->Amount->clear();
	m_ui->Priority->clear();
	m_ui->BuyUntil->clear();
	m_ui->Name->clear();
	m_ui->IsBought->setChecked(false);
}

void ProductQuickCreateSubPage::SetRangeOfSpinBox()
{
	m_ui->Amount->setRange(1, 100); // need to be changed do not hardcode
	m_ui->Priority->setRange(1, 5);
}

void ProductQuickCreateSubPage::SetMinimumDate(const QDate& date)
{
	m_ui->BuyUntil->setMinimumDate(date);
}
