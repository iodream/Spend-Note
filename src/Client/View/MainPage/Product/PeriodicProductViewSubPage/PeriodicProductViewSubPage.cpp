#include "PeriodicProductViewSubPage.h"
#include "ui_PeriodicProductViewSubPage.h"

PeriodicProductViewSubPage::PeriodicProductViewSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::PeriodicProductViewSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		this,
		&PeriodicProductViewSubPage::CreateProduct);

	m_ui->GenerateUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());

	m_ui->GenerateUntil->setDate(QDate::currentDate());
	SetMinimumDate(QDate::currentDate());

	connect(
		m_ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&PeriodicProductViewSubPage::OnNewCategoryPushed);
	connect(
		m_ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&PeriodicProductViewSubPage::OnNewCategorySaved);

	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
}

PeriodicProductViewSubPage::~PeriodicProductViewSubPage()
{
	delete m_ui;
}

QString PeriodicProductViewSubPage::GetName()
{
	return m_ui->Name->text();
}

Money PeriodicProductViewSubPage::GetPrice()
{
	return m_ui->Price->value();
}

BigInt PeriodicProductViewSubPage::GetAmount()
{
	return m_ui->Amount->value();
}

QString PeriodicProductViewSubPage::GetGenerateUntil()
{
	return toDBstring(m_ui->GenerateUntil->dateTime());
}

BigInt PeriodicProductViewSubPage::GetPriority()
{
	return m_ui->Priority->value();
}

IdType PeriodicProductViewSubPage::GetCategoryId()
{
	return qvariant_cast<IdType>(m_ui->Category->currentData());
}

QString PeriodicProductViewSubPage::GetCategoryName()
{
	return m_ui->Category->currentText();
}

void PeriodicProductViewSubPage::Clear()
{
	m_ui->Name->clear();
	m_ui->Price->clear();
	m_ui->Amount->clear();
	m_ui->Priority->clear();
	m_ui->GenerateUntil->clear();
	m_ui->Name->clear();
}

void PeriodicProductViewSubPage::FillCategoryBox(const std::vector<ProductCategory> &categories)
{
	m_ui->Category->clear();
	for(const auto& el : categories)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
}

void PeriodicProductViewSubPage::SetRangeOfSpinBox()
{
	m_ui->Amount->setRange(1, 100); // need to be changed do not hardcode
	m_ui->Priority->setRange(1, 5);
}

void PeriodicProductViewSubPage::SetMinimumDate(const QDate& date)
{
	m_ui->GenerateUntil->setMinimumDate(date);
	m_ui->AddedDate->setMinimumDate(date);
}

void PeriodicProductViewSubPage::OnNewCategoryPushed()
{
	m_ui->NewCategoryName->setVisible(true);
	m_ui->NewCategorySaveButton->setVisible(true);
	m_ui->NewCategoryButton->setDisabled(true);
}

void PeriodicProductViewSubPage::OnNewCategorySaved()
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
