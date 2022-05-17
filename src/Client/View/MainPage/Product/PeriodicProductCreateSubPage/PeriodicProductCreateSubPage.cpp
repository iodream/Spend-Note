#include "PeriodicProductCreateSubPage.h"
#include "ui_PeriodicProductCreateSubPage.h"

PeriodicProductCreateSubPage::PeriodicProductCreateSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::PeriodicProductCreateSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		this,
		&PeriodicProductCreateSubPage::CreateProduct);

	m_ui->AddedDate->setDisplayFormat(
		QLocale::system().dateTimeFormat());

	m_ui->AddedDate->setDate(QDate::currentDate());
	SetMinimumDate(QDate::currentDate());

	m_ui->GenerateUntil->setDisplayFormat(
		QLocale::system().dateTimeFormat());

	m_ui->GenerateUntil->setDate(QDate::currentDate());
	SetMinimumDate(QDate::currentDate());

	connect(
		m_ui->NewCategoryButton,
		&QPushButton::released,
		this,
		&PeriodicProductCreateSubPage::OnNewCategoryPushed);
	connect(
		m_ui->NewCategorySaveButton,
		&QPushButton::released,
		this,
		&PeriodicProductCreateSubPage::OnNewCategorySaved);

	m_ui->NewCategoryName->setVisible(false);
	m_ui->NewCategorySaveButton->setVisible(false);
}

PeriodicProductCreateSubPage::~PeriodicProductCreateSubPage()
{
	delete m_ui;
}

QString PeriodicProductCreateSubPage::GetName()
{
	return m_ui->Name->text();
}

Money PeriodicProductCreateSubPage::GetPrice()
{
	return m_ui->Price->value();
}

BigInt PeriodicProductCreateSubPage::GetAmount()
{
	return m_ui->Amount->value();
}

QString PeriodicProductCreateSubPage::GetGenerateUntil()
{
	return toDBstring(m_ui->GenerateUntil->dateTime());
}

BigInt PeriodicProductCreateSubPage::GetPriority()
{
	return m_ui->Priority->value();
}

IdType PeriodicProductCreateSubPage::GetCategoryId()
{
	return qvariant_cast<IdType>(m_ui->Category->currentData());
}

QString PeriodicProductCreateSubPage::GetCategoryName()
{
	return m_ui->Category->currentText();
}

QString PeriodicProductCreateSubPage::GetAddNext()
{
	return toDBstring(m_ui->AddedDate->dateTime());
}

IdType PeriodicProductCreateSubPage::GetPeriodId()
{
	return m_ui->RepeatingSelect->currentIndex() + 1; // hardcoded db index from combobox index
}

void PeriodicProductCreateSubPage::Clear()
{
	m_ui->Name->clear();
	m_ui->Price->clear();
	m_ui->Amount->clear();
	m_ui->Priority->clear();
	m_ui->GenerateUntil->clear();
	m_ui->Name->clear();}

void PeriodicProductCreateSubPage::FillCategoryBox(const std::vector<ProductCategory> &categories)
{
	m_ui->Category->clear();
	for(const auto& el : categories)
	{
		m_ui->Category->addItem(el.name, el.id);
	}
}

void PeriodicProductCreateSubPage::SetRangeOfSpinBox()
{
	m_ui->Amount->setRange(1, 100); // need to be changed do not hardcode
	m_ui->Priority->setRange(1, 5);
}

void PeriodicProductCreateSubPage::SetMinimumDate(const QDate& date)
{
	m_ui->GenerateUntil->setMinimumDate(date);
	m_ui->AddedDate->setMinimumDate(date);

}

void PeriodicProductCreateSubPage::OnNewCategoryPushed()
{
	m_ui->NewCategoryName->setVisible(true);
	m_ui->NewCategorySaveButton->setVisible(true);
	m_ui->NewCategoryButton->setDisabled(true);
}

void PeriodicProductCreateSubPage::OnNewCategorySaved()
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
