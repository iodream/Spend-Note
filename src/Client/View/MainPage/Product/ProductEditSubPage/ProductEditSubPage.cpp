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

	m_ui->BuyUntil->setDate(QDate::currentDate());
	SetMinimumDate(QDate::currentDate());
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
	m_product.amount = m_ui->Amount->value();
	m_product.buy_until_date = toDBstring(m_ui->BuyUntil->dateTime());
	m_product.priority = m_ui->Priority->value();
	m_product.category.id = 1 + m_ui->Category->currentIndex();
	m_product.is_bought = m_ui->IsBought->isChecked();
	return m_product;
}

void ProductEditSubPage::Update()
{
	m_ui->Name->setText(m_product.name);
	m_ui->Price->setText(QString::number(m_product.price));
	m_ui->Amount->setDisplayIntegerBase(m_product.amount);
	m_ui->BuyUntil->setDateTime(QDateTime::fromString(m_product.buy_until_date, "yyyy-mm-dd HH:mm:ss.zzz"));
	m_ui->Priority->setDisplayIntegerBase(m_product.priority);
	m_ui->Category->setPlaceholderText(m_product.category.name);
	m_ui->IsBought->setChecked(m_product.is_bought);
}

void ProductEditSubPage::FillCategoryBox(const std::vector<ProductCategory> &categories)
{
	for(const auto& el : categories)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
}

void ProductEditSubPage::SetRangeOfSpinBox()
{
	m_ui->Amount->setRange(1, 100); // need to be changed do not hardcode
	m_ui->Priority->setRange(1, 5);
}

void ProductEditSubPage::SetMinimumDate(const QDate& date)
{
	m_ui->BuyUntil->setMinimumDate(date);
}
