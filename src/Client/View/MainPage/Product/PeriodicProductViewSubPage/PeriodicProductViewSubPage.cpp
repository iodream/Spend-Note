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

	QDateTime add_date = QDateTime::fromString(
		m_product.next_add_date,
		DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);
	m_ui->AddedDate->setText(QLocale::system().toString(add_date, QLocale::system().dateTimeFormat()));

	QDateTime add_until_date = QDateTime::fromString(
		m_product.add_until,
		DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);
	m_ui->GenerateUntil->setText(QLocale::system().toString(add_until_date, QLocale::system().dateTimeFormat()));

	const std::array periods = {
		"Daily",
		"Weekly",
		"Monthly",
		"Yearly"
	};

	m_ui->Repeating->setText(periods[m_product.period_id - 1]);
	m_ui->Priority->setText(QString::number(m_product.priority));
	m_ui->Category->setText(m_product.category.name);
}

void PeriodicProductViewSubPage::set_product(const PeriodicProduct& product)
{
	m_product = product;
}

PeriodicProduct PeriodicProductViewSubPage::get_product()
{
	return m_product;
}
