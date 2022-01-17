#include "ListItem.h"
#include "ui_ListItem.h"

#include "View/Constants.h"

namespace {

const QString DEFAULT_COLOR_ODD  = "rgba(255, 255, 255, 50%)";
const QString DEFAULT_COLOR_EVEN = "rgba(235, 235, 235, 50%)";

}

#include <iostream>

ListItem::ListItem(IdType id, QWidget *parent)
	: QPushButton(parent)
	, m_id(id)
	, ui(new Ui::ListItem)
{
	ui->setupUi(this);
}

ListItem::~ListItem()
{
	delete ui;
}

void ListItem::UpdateColor()
{
	bool is_odd = m_number % 2;
	if (is_odd) {
		m_color = DEFAULT_COLOR_ODD;
	}
	else {
		m_color = DEFAULT_COLOR_EVEN;
	}
}

void ListItem::Update()
{
	ui->ProductName->setText(m_name);
	ui->BuyUntil->setText(m_buy_until);
	ui->Price->setText(m_price);
	ui->Number->setText(QString("%1").arg(m_number));
	UpdateColor();
	ui->Holder->setStyleSheet(
		QString("%1 %2;").arg(STYLESHEET_BACKGROUND_COLOR, m_color));
	ui->Holder->show();
}

void ListItem::set_number(int number)
{
	m_number = number;
	Update();
}

int ListItem::get_number()
{
	return m_number;
}

void ListItem::set_name(QString name)
{
	m_name = name;
}

void ListItem::set_buy_until(QString buy_until)
{
	m_buy_until = buy_until;
}

void ListItem::set_price(QString price)
{
	m_price = price;
}

void ListItem::set_is_purchased(bool is_purchased)
{
	m_is_purchased = is_purchased;
}

QString ListItem::get_color()
{
	return m_color;
}
