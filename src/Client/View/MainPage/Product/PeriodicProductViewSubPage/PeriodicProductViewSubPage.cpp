#include "PeriodicProductViewSubPage.h"
#include "ui_PeriodicProductViewSubPage.h"

PeriodicProductViewSubPage::PeriodicProductViewSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::PeriodicProductViewSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->EditButton,
		&QPushButton::clicked,
		this,
		&PeriodicProductViewSubPage::EditProduct);
	connect(
		m_ui->DeleteButton,
		&QPushButton::clicked,
		this,
		&PeriodicProductViewSubPage::DeleteProduct);
}

PeriodicProductViewSubPage::~PeriodicProductViewSubPage()
{
	delete m_ui;
}

void PeriodicProductViewSubPage::Update()
{
	m_ui->Name->setText(m_product.name);
	m_ui->Price->setText(QString::number(m_product.price));
	m_ui->Amount->setText(QString::number(m_product.amount));

	QDateTime date = QDateTime::fromString(
		m_product.buy_until_date, DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);

	m_ui->GenerateUntil->setText(QLocale::system().toString(date, QLocale::system().dateTimeFormat()));
	m_ui->Priority->setText(QString::number(m_product.priority));
	m_ui->Category->setText(m_product.category.name);
}

void PeriodicProductViewSubPage::set_product(const Product& product)
{
	m_product = product;
}

Product PeriodicProductViewSubPage::get_product()
{
	return m_product;
}
