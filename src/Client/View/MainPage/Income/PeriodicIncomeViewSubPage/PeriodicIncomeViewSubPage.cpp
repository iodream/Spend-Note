#include "PeriodicIncomeViewSubPage.h"
#include "ui_PeriodicIncomeViewSubPage.h"

#include <QPushButton>
#include "Exception.h"
#include "Net/Parsing.h"
#include "Models/List/GetListsModel.h"

PeriodicIncomeViewSubPage::PeriodicIncomeViewSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::PeriodicIncomeViewSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->EditButton,
		&QPushButton::clicked,
		[this](){ emit GoToEditIncome(m_income); });

	connect(
		m_ui->DeleteButton,
		&QPushButton::clicked,
		[this](){ emit DeleteIncome(m_income); });
}

PeriodicIncomeViewSubPage::~PeriodicIncomeViewSubPage()
{
	delete m_ui;
}

void PeriodicIncomeViewSubPage::set_income(const Income& Income)
{
	m_income = Income;
}

Income PeriodicIncomeViewSubPage::get_income() const
{
	return m_income;
}

void PeriodicIncomeViewSubPage::Update(const Income& Income)
{
	set_income(Income);
	m_ui->Name->setText(m_income.name);
	m_ui->Amount->setText(QString::number(m_income.amount));
	m_ui->Category->setText(m_income.category.name);

}
