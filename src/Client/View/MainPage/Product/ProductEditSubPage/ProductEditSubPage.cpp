#include "ProductEditSubPage.h"
#include "ui_ProductEditSubPage.h"

ProductEditSubPage::ProductEditSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductEditSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		this,
		&ProductEditSubPage::UpdateProduct);
}

ProductEditSubPage::~ProductEditSubPage()
{
	delete m_ui;
}

void ProductEditSubPage::set_product(const Product& product)
{
	m_product = product;
}

Product ProductEditSubPage::get_product()
{
	m_product.name = m_ui->Name->text();
	m_product.price = m_ui->Price->text().toLongLong();
	m_product.amount = m_ui->Amount->text().toLongLong();
	m_product.buy_until_date = m_ui->BuyUntil->text();
	m_product.priority = m_ui->Priority->text().toLongLong();
	m_product.is_bought = m_ui->IsBought->isChecked();
	return m_product;
}

void ProductEditSubPage::Update()
{
	m_ui->Name->setText(m_product.name);
	m_ui->Price->setText(QString::number(m_product.price));
	m_ui->Amount->setText(QString::number(m_product.amount));
	m_ui->BuyUntil->setText(m_product.buy_until_date);
	m_ui->Priority->setText(QString::number(m_product.priority));
	m_ui->Category->addItem(m_product.category.name);
	m_ui->IsBought->setChecked(m_product.is_bought);
}
