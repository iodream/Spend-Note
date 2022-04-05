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


	m_ui->BuyUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());

	m_ui->BuyUntil->setDate(QDate::currentDate());
	SetMinimumDate(QDate::currentDate());

	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);

	connect(
		m_ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&ProductEditSubPage::OnNewCategoryPushed);
	connect(
		m_ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&ProductEditSubPage::OnNewCategorySaved);
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
	m_product.price = m_ui->Price->value();
	m_product.amount = m_ui->Amount->value();
	m_product.buy_until_date = toDBstring(m_ui->BuyUntil->dateTime());
	m_product.priority = m_ui->Priority->value();
	m_product.category.id = qvariant_cast<IdType>(m_ui->Category->currentData());
	m_product.is_bought = m_ui->IsBought->isChecked();
	return m_product;
}

void ProductEditSubPage::Update()
{
	m_ui->Name->setText(m_product.name);
	m_ui->Price->setValue(m_product.price);
	m_ui->Amount->setValue(m_product.amount);
	m_ui->BuyUntil->setDateTime(QDateTime::fromString(m_product.buy_until_date, "yyyy-mm-dd HH:mm:ss.zzz"));
	m_ui->Priority->setValue(m_product.priority);
	m_ui->Category->setPlaceholderText(m_product.category.name);
	m_ui->Category->setCurrentIndex(m_ui->Category->findData(m_product.category.id));
	m_ui->IsBought->setChecked(m_product.is_bought);
}

void ProductEditSubPage::FillCategoryBox(const std::vector<ProductCategory> &categories)
{
	for(const auto& el : categories)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
	m_ui->Category->setCurrentIndex(0);
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

void ProductEditSubPage::OnNewCategoryPushed()
{
	m_ui->NewCategoryName->setVisible(true);
	m_ui->NewCategorySaveButton->setVisible(true);
	m_ui->NewCategoryButton->setDisabled(true);
}

void ProductEditSubPage::OnNewCategorySaved()
{
	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
	m_ui->NewCategoryButton->setDisabled(false);
}
