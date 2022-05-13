#pragma once

#include <QString>
#include <QWidget>

#include "IncomeListItem.h"

namespace Ui {
class IncomeListSubPage;
}

class IncomeListSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit IncomeListSubPage(QWidget *parent=nullptr);
	~IncomeListSubPage();

	void AppendRegularIncome(IncomeListItem* income);
	void InsertRegularIncome(IncomeListItem* income, int idx);
	void RemoveRegularIncome(IncomeListItem* income);

	void UpdateNumbers(int idx);

	IncomeListItem* SafeGetRegularIncome(int idx);

	void Update(const std::vector<Income>& incomes);
	void Clear();

	void changeEvent(QEvent* event);

	void set_regular_list_size(int size);
	int get_regular_list_size();
	void UpdateColors();

private:
	Ui::IncomeListSubPage *m_ui;

	int m_regular_list_size, m_periodic_list_size;

signals:
	void GoToCreateIncome();
	void GoToIncomeView(const Income& income);
	void IncomeClicked(const Income& income);

private slots:
	void OnIncomeClicked(IncomeListItem* income);
};
