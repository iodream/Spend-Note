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

void ProductPage::Setup(ListItem* list_item)
{
	m_ui->name->setText(list_item->get_name());
	m_ui->buyUntil->setText(list_item->get_buy_until());
	m_ui->id->setText(QString::number(list_item->get_id()));
	m_ui->price->setText(list_item->get_price());
	m_ui->isPurchased->setChecked(list_item->get_is_purchased());
}

void ProductPage::OnGoBackClicked()
{
	this->~ProductPage();
}
