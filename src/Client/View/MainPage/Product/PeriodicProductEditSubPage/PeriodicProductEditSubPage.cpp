#include "PeriodicProductEditSubPage.h"
#include "ui_PeriodicProductEditSubPage.h"

PeriodicProductEditSubPage::PeriodicProductEditSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::PeriodicProductEditSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		this,
		&PeriodicProductEditSubPage::CreateProduct);

	m_ui->GenerateUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());

	m_ui->GenerateUntil->setDate(QDate::currentDate());
	SetMinimumDate(QDate::currentDate());

	connect(
		m_ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&PeriodicProductEditSubPage::OnNewCategoryPushed);
	connect(
		m_ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&PeriodicProductEditSubPage::OnNewCategorySaved);

	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
}

PeriodicProductEditSubPage::~PeriodicProductEditSubPage()
{
	delete m_ui;
}

QString PeriodicProductEditSubPage::GetName()
{
	return m_ui->Name->text();
}

Money PeriodicProductEditSubPage::GetPrice()
{
	return m_ui->Price->value();
}

BigInt PeriodicProductEditSubPage::GetAmount()
{
	return m_ui->Amount->value();
}

QString PeriodicProductEditSubPage::GetGenerateUntil()
{
	return toDBstring(m_ui->GenerateUntil->dateTime());
}

BigInt PeriodicProductEditSubPage::GetPriority()
{
	return m_ui->Priority->value();
}

IdType PeriodicProductEditSubPage::GetCategoryId()
{
	return qvariant_cast<IdType>(m_ui->Category->currentData());
}

QString PeriodicProductEditSubPage::GetCategoryName()
{
	return m_ui->Category->currentText();
}

void PeriodicProductEditSubPage::Clear()
{
	m_ui->Name->clear();
	m_ui->Price->clear();
	m_ui->Amount->clear();
	m_ui->Priority->clear();
	m_ui->GenerateUntil->clear();
	m_ui->Name->clear();
}

void PeriodicProductEditSubPage::FillCategoryBox(const std::vector<ProductCategory> &categories)
{
	m_ui->Category->clear();
	for(const auto& el : categories)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
}

void PeriodicProductEditSubPage::SetRangeOfSpinBox()
{
	m_ui->Amount->setRange(1, 100); // need to be changed do not hardcode
	m_ui->Priority->setRange(1, 5);
}

void PeriodicProductEditSubPage::SetMinimumDate(const QDate& date)
{
	m_ui->GenerateUntil->setMinimumDate(date);
	m_ui->AddDate->setMinimumDate(date);

}

void PeriodicProductEditSubPage::OnNewCategoryPushed()
{
	m_ui->NewCategoryName->setVisible(true);
	m_ui->NewCategorySaveButton->setVisible(true);
	m_ui->NewCategoryButton->setDisabled(true);
}

void PeriodicProductEditSubPage::OnNewCategorySaved()
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
