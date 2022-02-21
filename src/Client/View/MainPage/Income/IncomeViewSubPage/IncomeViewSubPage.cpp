#include "IncomeViewSubPage.h"
#include "ui_IncomeViewSubPage.h"

#include <QPushButton>
#include "Exception.h"
#include "Net/Parsing.h"
#include "Models/List/GetListsModel.h"

IncomeViewSubPage::IncomeViewSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::IncomeViewSubPage)
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

IncomeViewSubPage::~IncomeViewSubPage()
{
	delete m_ui;
}

void IncomeViewSubPage::set_income(const Income& income)
{
	m_income = income;
}

Income IncomeViewSubPage::get_income() const
{
	return m_income;
}

void IncomeViewSubPage::Update(const Income& income)
{
	set_income(income);
	m_ui->Name->setText(m_income.name);
	m_ui->Amount->setText(QString::number(m_income.amount));
	m_ui->Category->setText(m_income.category.name);
	m_ui->Expires->setText(m_income.expiration_time);
}
