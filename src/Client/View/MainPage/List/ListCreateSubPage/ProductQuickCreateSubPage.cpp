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
	return m_ui->Amount->text().toLongLong();
}

bool ProductQuickCreateSubPage::GetIsBought()
{
	return m_ui->IsBought->isChecked();
}

QString ProductQuickCreateSubPage::GetBuyUntil()
{
	return m_ui->BuyUntil->text();
}

BigInt ProductQuickCreateSubPage::GetPriority()
{
	return m_ui->Priority->text().toLongLong();
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
