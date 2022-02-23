#include <iostream>

#include "ListItem.h"
#include "ui_ListItem.h"

#include "View/Constants.h"

namespace {

const QString COLOR_STATE_ACTIVE  = "rgba(163, 255, 188, 50%)";
const QString COLOR_STATE_INACTIVE  = "rgba(41, 118, 207, 50%)";

}

ListItem::ListItem(List list, QWidget *parent)
	: QPushButton(parent)
	, m_list(list)
	, m_ui(new Ui::ListItem)
{
	m_ui->setupUi(this);
}

ListItem::~ListItem()
{
	delete m_ui;
}

void ListItem::UpdateColor(const ListState& state)
{
	if(state.name == "active")
	{
		m_color = COLOR_STATE_ACTIVE;
	}
	else
	{
		m_color = COLOR_STATE_INACTIVE;
	}
}

void ListItem::Update()
{
	m_ui->ListName->setText(m_list.name);
	m_ui->Number->setText(QString("%1").arg(m_number));
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

QString ListItem::get_color()
{
	return m_color;
}

