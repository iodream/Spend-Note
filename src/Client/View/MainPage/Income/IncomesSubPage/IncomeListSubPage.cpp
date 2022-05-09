#include "IncomeListSubPage.h"
#include "ui_IncomeListSubPage.h"

#include "Exception.h"

#include "View/MainPage/MainPage.h"

IncomeListSubPage::IncomeListSubPage(QWidget* parent)
	: QWidget(parent)
	, m_ui(new Ui::IncomeListSubPage)
{
	m_ui->setupUi(this);
	set_regular_list_size(0);

	connect(
		m_ui->AddIncomeButton,
		&QPushButton::clicked,
		this,
		&IncomeListSubPage::GoToCreateIncome);
}

void IncomeListSubPage::AppendRegularIncome(IncomeListItem* income)
{
	InsertRegularIncome(income, get_regular_list_size());
}

void IncomeListSubPage::InsertRegularIncome(IncomeListItem* income, int idx)
{
	if (get_regular_list_size() < idx || idx < 0) {
		throw Exception("Trying to insert a widget out of range");
	}
	m_ui->RegularIncomesLayout->insertWidget(idx, income);

	connect(
		income,
		&IncomeListItem::clicked,
		[this, income](){ OnIncomeClicked(income); });

	income->set_number(idx + 1);
	set_regular_list_size(get_regular_list_size() + 1);
	UpdateNumbers(idx + 1);
}

void IncomeListSubPage::UpdateNumbers(int idx)
{
	while (idx < get_regular_list_size())
	{
		auto* income = SafeGetRegularIncome(idx);
		income->set_number(++idx);
		income->Update();
	}
}

void IncomeListSubPage::RemoveRegularIncome(IncomeListItem* income)
{
	int idx = income->get_number() - 1;
	QLayoutItem *layout = m_ui->RegularIncomesLayout->takeAt(idx);
	if (!layout) {
		throw Exception("Failed to get income layout");
	}

	delete layout->widget();
	delete layout;
	set_regular_list_size(get_regular_list_size() - 1);

	UpdateNumbers(idx);
}

void IncomeListSubPage::OnIncomeClicked(IncomeListItem* income)
{
	emit GoToIncomeView(income->get_income());
}

IncomeListItem* IncomeListSubPage::SafeGetRegularIncome(int idx)
{
	QLayoutItem *layout = m_ui->RegularIncomesLayout->itemAt(idx);
	if (!layout) {
		throw Exception("Failed to get income layout");
	}
	auto* income = qobject_cast<IncomeListItem*>(layout->widget());
	if (!income) {
		throw Exception("Failed to get income widget pointer");
	}
	return income;
}

void IncomeListSubPage::set_regular_list_size(int size)
{
	m_regular_list_size = size;
	//m_ui->ListSize->setText(QString("%1").arg(m_list_size));
	//m_ui->ListSize->show();
}

int IncomeListSubPage::get_regular_list_size()
{
	return m_regular_list_size;
}

void IncomeListSubPage::Update(const std::vector<Income>& incomes)
{
	Clear();
	for (auto it = incomes.begin(); it != incomes.end(); it++) {
		IncomeListItem* item = new IncomeListItem(*it);
		item->Update();
		AppendRegularIncome(item);
	}
}

void IncomeListSubPage::UpdateColors()
{
	m_ui->frame->setStyleSheet("background-color:" + QString(MainPage::ColorSettings::COLOR_TOP_BANNER));
}

void IncomeListSubPage::Clear()
{
	while (get_regular_list_size()) {
		QLayoutItem *layout = m_ui->RegularIncomesLayout->takeAt(0);
		if (!layout) {
			throw Exception("Failed to get product layout");
		}

		delete layout->widget();
		delete layout;
		set_regular_list_size(get_regular_list_size() - 1);
	}
}

IncomeListSubPage::~IncomeListSubPage()
{
	delete m_ui;
}
