#include "ProductViewSubPage.h"
#include "ui_ProductViewSubPage.h"

#include "Entities/Entities.h"

ProductViewSubPage::ProductViewSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductViewSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->EditButton,
		&QPushButton::clicked,
		this,
		&ProductViewSubPage::EditProduct);

	connect(
		m_ui->GoBackButton,
		&QPushButton::clicked,
		this,
		&ProductViewSubPage::GoBack);

	connect(
		m_ui->DeleteButton,
		&QPushButton::clicked,
		this,
		&ProductViewSubPage::DeleteProduct);
}

ProductViewSubPage::~ProductViewSubPage()
{
	delete m_ui;
}

void ProductViewSubPage::Update(const Product& product)
{
	m_ui->Name->setText(product.name);
	m_ui->Price->setText(product.price);
	m_ui->Amount->setText(product.amount);
	m_ui->BuyUntil->setText(product.buy_until_date);
	m_ui->Priority->setText(product.priority);
	m_ui->Category->setText(product.category.name);
	m_ui->IsBought->setChecked(product.is_bought);
}
