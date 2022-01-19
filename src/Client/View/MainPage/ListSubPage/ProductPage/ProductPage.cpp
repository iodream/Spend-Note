#include "ProductPage.h"
#include "ui_ProductPage.h"

ProductPage::ProductPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductPage)
{
	m_ui->setupUi(this);

	connect(m_ui->goBackButton, SIGNAL(clicked()), this, SLOT(OnGoBackClicked()));
}

ProductPage::~ProductPage()
{
	delete m_ui;
}

void ProductPage::Setup(QString name, int id, QString buy_until, QString price, bool is_purchased)
{
	m_ui->name->setText(name);
	m_ui->buyUntil->setText(buy_until);
	m_ui->id->setText(QString::number(id));
	m_ui->price->setText(price);
	m_ui->isPurchased->setChecked(is_purchased);
}

void ProductPage::OnGoBackClicked()
{
	this->~ProductPage();
}
