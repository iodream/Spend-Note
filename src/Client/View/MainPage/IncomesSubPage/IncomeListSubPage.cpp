#include "IncomeListSubPage.h"
#include "ui_IncomeListSubPage.h"

#include "Exception.h"

#include <iostream>

IncomeListSubPage::IncomeListSubPage(int id, QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::IncomeListSubPage)
	, m_id(id)
{
	m_ui->setupUi(this);
	set_list_size(0);

	connect(m_ui->addIncomeButton, SIGNAL(released()), this, SLOT(OnAddIncome()));
}

void IncomeListSubPage::OnAddIncome()
{
	int id = get_list_size();
	IncomeListItem* income = new IncomeListItem(id);
	income->set_name(QString("income %1").arg(id));
	income->set_amount(100);
	income->set_category("Test category");
	income->set_expiration_time("2022-01-21");
	income->Update();
//	Appendincome(income);
	InsertIncome(income, 0);
}

void IncomeListSubPage::OnIncomeClicked()
{
	IncomeListItem* income = qobject_cast<IncomeListItem*>(sender());
	if (!income) {
		throw Exception("Failed to get caller object pointer");
	}

	RemoveIncome(income);
}

IncomeListItem* IncomeListSubPage::SafeGetIncome(int idx)
{
	QLayoutItem *layout = m_ui->ItemsLayout->itemAt(idx);
	if (!layout) {
		throw Exception("Failed to get income layout");
	}
	auto* income = qobject_cast<IncomeListItem*>(layout->widget());
	if (!income) {
		throw Exception("Failed to get income widget pointer");
	}
	return income;
}

void IncomeListSubPage::RemoveIncome(IncomeListItem* income)
{
	int idx = income->get_number() - 1;
	QLayoutItem *layout = m_ui->ItemsLayout->takeAt(idx);
	if (!layout) {
		throw Exception("Failed to get income layout");
	}

	delete layout->widget();
	delete layout;
	set_list_size(get_list_size() - 1);

	UpdateNumbers(idx);
}

void IncomeListSubPage::UpdateNumbers(int idx)
{
	while (idx < get_list_size())
	{
		auto* income = SafeGetIncome(idx);
		income->set_number(++idx);
		income->Update();
	}
}

void IncomeListSubPage::set_list_size(int size)
{
	m_list_size = size;
	/*m_ui->ListSize->setText(QString("%1").arg(m_list_size));
	m_ui->ListSize->show();*/
}

int IncomeListSubPage::get_list_size()
{
	return m_list_size;
}

IncomeListSubPage::~IncomeListSubPage()
{
	delete m_ui;
}

void IncomeListSubPage::AppendIncome(IncomeListItem* income)
{
	InsertIncome(income, get_list_size());
}

void IncomeListSubPage::InsertIncome(IncomeListItem* income, int idx)
{
	if (get_list_size() < idx || idx < 0) {
		throw Exception("Trying to insert a widget out of range");
	}
	m_ui->ItemsLayout->insertWidget(idx, income);
	connect(income, SIGNAL(released()), this, SLOT(OnIncomeClicked()));
	income->set_number(idx + 1);
	set_list_size(get_list_size() + 1);
	UpdateNumbers(idx + 1);
}
