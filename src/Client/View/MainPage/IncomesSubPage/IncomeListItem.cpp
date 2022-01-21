#include "IncomeListItem.h"
#include "ui_IncomeListItem.h"

#include "View/Constants.h"

namespace {

const QString DEFAULT_COLOR_ODD  = "rgba(255, 255, 255, 50%)";
const QString DEFAULT_COLOR_EVEN = "rgba(235, 235, 235, 50%)";

}

#include <iostream>

IncomeListItem::IncomeListItem(IdType id, QWidget *parent)
	: QPushButton(parent)
	, m_id(id)
	, m_ui(new Ui::IncomeListItem)
{
	m_ui->setupUi(this);
}

IncomeListItem::~IncomeListItem()
{
	delete m_ui;
}

void IncomeListItem::UpdateColor()
{
	bool is_odd = m_number % 2;
	if (is_odd) {
		m_color = DEFAULT_COLOR_ODD;
	}
	else {
		m_color = DEFAULT_COLOR_EVEN;
	}
}

void IncomeListItem::Update()
{
	m_ui->incomeName->setText(m_name);
	m_ui->expirationTime->setText(m_expiration_time);
	m_ui->amount->setText(QString::number(m_amount));
	m_ui->category->setText(m_category);
	m_ui->number->setText(QString("%1").arg(m_number));
	UpdateColor();
	m_ui->Holder->setStyleSheet(
		QString("%1 %2;").arg(STYLESHEET_BACKGROUND_COLOR, m_color));
	m_ui->Holder->show();
}

void IncomeListItem::set_name(const QString& name)
{
	m_name = name;
}

void IncomeListItem::set_amount(int amount)
{
	m_amount = amount;
}

void IncomeListItem::set_expiration_time(const QString& expiration_time)
{
	m_expiration_time = expiration_time;
}

void IncomeListItem::set_category(const QString& category)
{
	m_category = category;
}

void IncomeListItem::set_number(int number)
{
	m_number = number;
	Update();
}

int IncomeListItem::get_number()
{
	return m_number;
}

QString IncomeListItem::get_color()
{
	return m_color;
}
