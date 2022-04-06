#include "ProductViewSubPage.h"
#include "ui_ProductViewSubPage.h"

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
		m_ui->DeleteButton,
		&QPushButton::clicked,
		this,
		&ProductViewSubPage::DeleteProduct);
}

ProductViewSubPage::~ProductViewSubPage()
{
	delete m_ui;
}

void ProductViewSubPage::Update()
{
	m_ui->Name->setText(m_product.name);
	m_ui->Price->setText(QString::number(m_product.price));
	m_ui->Amount->setText(QString::number(m_product.amount));

	QDateTime date = QDateTime::fromString(
		m_product.buy_until_date, DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);

	m_ui->BuyUntil->setText(QLocale::system().toString(date, QLocale::system().dateTimeFormat()));
	m_ui->Priority->setText(QString::number(m_product.priority));
	m_ui->Category->setText(m_product.category.name);
	m_ui->IsBought->setText(m_product.is_bought ? "Yes" : "No");
}

void ProductViewSubPage::set_product(const Product& product)
{
	m_product = product;
}

Product ProductViewSubPage::get_product()
{
	return m_product;
}
