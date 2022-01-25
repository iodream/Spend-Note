#include "ProductItem.h"
#include "ui_ProductItem.h"

#include "View/Constants.h"

namespace {

const QString DEFAULT_COLOR_ODD  = "rgba(255, 255, 255, 50%)";
const QString DEFAULT_COLOR_EVEN = "rgba(235, 235, 235, 50%)";

}

#include <iostream>

ProductItem::ProductItem(IdType id, QWidget *parent)
	: QPushButton(parent)
	, m_id(id)
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
	m_ui->ProductName->setText(m_name);
	m_ui->BuyUntil->setText(m_buy_until);
	m_ui->Price->setText(m_price);
	m_ui->Number->setText(QString("%1").arg(m_number));
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

void ProductItem::set_name(const QString& name)
{
	m_name = name;
}

void ProductItem::set_buy_until(const QString& buy_until)
{
	m_buy_until = buy_until;
}

void ProductItem::set_price(const QString& price)
{
	m_price = price;
}

void ProductItem::set_is_purchased(bool is_purchased)
{
	m_is_purchased = is_purchased;
}

QString ProductItem::get_color()
{
	return m_color;
}
