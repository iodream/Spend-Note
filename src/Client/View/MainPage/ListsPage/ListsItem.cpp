#include <iostream>

#include "ListsItem.h"
#include "ui_ListsItem.h"

#include "View/Constants.h"
#include "../MainPage.h"
ListsItem::ListsItem(IdType id, const QString& listName, const QString& Status, QWidget *parent)
	: QPushButton(parent)
	, m_id(id)
	, m_color(Status)
	, m_name(listName)
	, m_ui(new Ui::ListsItem)
{
	m_ui->setupUi(this);
	m_ui->IdNumber->setText(QString::number(m_id));
	m_ui->ListName->setText(m_name);
	//m_ui->ItemsHolder->setStyleSheet(QString("%1 %2;").arg(STYLESHEET_BACKGROUND_COLOR, m_color)); //bg color is still not good
}

ListsItem::~ListsItem()
{
	delete m_ui;
}
