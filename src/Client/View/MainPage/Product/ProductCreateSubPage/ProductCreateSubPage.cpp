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

	connect(
		m_ui->GoBackButton,
		&QPushButton::clicked,
		this,
		&ProductCreateSubPage::GoBack);
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
	return m_ui->Price->text().toLongLong();
}

BigInt ProductCreateSubPage::GetAmount()
{
	return m_ui->Amount->text().toLongLong();
}

bool ProductCreateSubPage::GetIsBought()
{
	return m_ui->IsBought->isChecked();
}

QString ProductCreateSubPage::GetBuyUntil()
{
	return m_ui->BuyUntil->text();
}

BigInt ProductCreateSubPage::GetPriority()
{
	return m_ui->Priority->text().toLongLong();
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
