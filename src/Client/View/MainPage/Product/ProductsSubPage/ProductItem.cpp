#include "ProductItem.h"
#include "ui_ProductItem.h"

#include "View/Constants.h"

namespace {

const QString DEFAULT_COLOR_ODD  = "rgba(255, 255, 255, 50%)";
const QString DEFAULT_COLOR_EVEN = "rgba(235, 235, 235, 50%)";

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
	bool is_odd = m_number % 2;
	if (is_odd) {
		m_color = DEFAULT_COLOR_ODD;
	}
	else {
		m_color = DEFAULT_COLOR_EVEN;
	}
}

void ProductItem::Update()
{
	m_ui->ProductName->setText(m_product.name);
	m_ui->BuyUntil->setText(m_product.buy_until_date);
	m_ui->Price->setText(QString("%1").arg(m_product.price));
	m_ui->Number->setText(QString("%1").arg(m_number));
	m_ui->PurchasedCheckbox->setChecked(m_product.is_bought);
	UpdateColor();
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
