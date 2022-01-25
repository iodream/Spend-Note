#include <iostream>

#include "ListItem.h"
#include "ui_ListItem.h"

#include "View/Constants.h"

namespace {

const QString DEFAULT_COLOR_ODD  = "rgba(255, 255, 255, 50%)";
const QString DEFAULT_COLOR_EVEN = "rgba(235, 235, 235, 50%)";

}

ListItem::ListItem(IdType id, QWidget *parent)
	: QPushButton(parent)
	, m_id(id)
	, m_ui(new Ui::ListItem)
{
	m_ui->setupUi(this);
}

ListItem::~ListItem()
{
	delete m_ui;
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
	m_ui->ListName->setText(m_name);
	m_ui->Number->setText(QString("%1").arg(m_number));
	UpdateColor();
	m_ui->Holder->setStyleSheet(
		QString("%1 %2;").arg(STYLESHEET_BACKGROUND_COLOR, m_color));
	m_ui->Holder->show();
}

void ListItem::set_number(int number)
{
	m_number = number;
	Update();
}

int ListItem::get_number() const
{
	return m_number;
}

void ListItem::set_name(const QString& name)
{
	m_name = name;
}

QString ListItem::get_color()
{
	return m_color;
}

