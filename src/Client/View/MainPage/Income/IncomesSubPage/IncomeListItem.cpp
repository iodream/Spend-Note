#include "IncomeListItem.h"
#include "ui_IncomeListItem.h"

#include "View/Constants.h"

namespace {

const QString DEFAULT_COLOR_ODD  = "rgba(255, 255, 255, 50%)";
const QString DEFAULT_COLOR_EVEN = "rgba(235, 235, 235, 50%)";

}

#include <iostream>

IncomeListItem::IncomeListItem(Income income, QWidget *parent)
	: QPushButton(parent)
	, m_income(income)
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
	m_ui->Name->setText(m_income.name);
	m_ui->ExpirationTime->setText(m_income.expiration_time);
	m_ui->Amount->setText(QString::number(m_income.amount));
	m_ui->Category->setText(m_income.category.name);
	m_ui->Number->setText(QString("%1").arg(m_number));

	UpdateColor();
	m_ui->Holder->setStyleSheet(
		QString("%1 %2;").arg(STYLESHEET_BACKGROUND_COLOR, m_color));
	m_ui->Holder->show();
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
