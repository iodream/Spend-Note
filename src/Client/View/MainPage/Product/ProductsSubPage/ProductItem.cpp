#include "ProductItem.h"
#include "ui_ProductItem.h"

#include "View/Constants.h"

namespace {

//const QString COLOR_BOUGHT = "rgba(23, 207, 63, 50%)";
//const QString COLOR_NOT_BOUGHT = "rgba(25, 96, 209, 50%)";
const QString COLOR_PRIO_ONE = "rgba(25, 96, 209, 50%)";
const QString COLOR_PRIO_TWO = "rgba(25, 209, 108, 50%)";
const QString COLOR_PRIO_THREE = "rgba(175, 209, 25, 50%)";
const QString COLOR_PRIO_FOUR = "rgba(209, 151, 25, 50%)";
const QString COLOR_PRIO_FIVE = "rgba(214, 108, 15, 50%)";


}

#include <iostream>

ProductItem::ProductItem(Product product, QWidget *parent)
	: QPushButton(parent)
	, m_product(product)
	, m_ui(new Ui::ProductItem)
{
	m_ui->setupUi(this);
}

ProductItem::~ProductItem()
{
	delete m_ui;
}

void ProductItem::UpdateColor()
{
	switch(m_product.priority)
	{
	case 1:
		m_color = COLOR_PRIO_ONE;
		break;
	case 2:
		m_color = COLOR_PRIO_TWO;
		break;
	case 3:
		m_color = COLOR_PRIO_THREE;
		break;
	case 4:
		m_color = COLOR_PRIO_FOUR;
		break;
	case 5:
		m_color = COLOR_PRIO_FIVE;
		break;
	}
}

void ProductItem::Update()
{
	m_ui->ProductName->setText(m_product.name);
	m_ui->BuyUntil->setText(m_product.buy_until_date);
	m_ui->Price->setText(QString("%1").arg(m_product.price));
	m_ui->Number->setText(QString("%1").arg(m_number));
	UpdateColor();
	if(m_product.is_bought)
		m_ui->PurchasedCheckbox->setChecked(true);
	else
		m_ui->PurchasedCheckbox->setChecked(false);
	m_ui->Holder->setStyleSheet(
		QString("%1 %2;").arg(STYLESHEET_BACKGROUND_COLOR, m_color));
	m_ui->Holder->show();
}

void ProductItem::set_number(int number)
{
	m_number = number;
	Update();
}

int ProductItem::get_number()
{
	return m_number;
}

QString ProductItem::get_color()
{
	return m_color;
}
