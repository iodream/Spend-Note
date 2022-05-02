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

	void AppendIncome(IncomeListItem* income);
	void InsertIncome(IncomeListItem* income, int idx);
	void RemoveIncome(IncomeListItem* income);

	void UpdateNumbers(int idx);

	IncomeListItem* SafeGetIncome(int idx);

	void Update(const std::vector<Income>& incomes);
	void Clear();

	void set_list_size(int size);
	int get_list_size();
	void UpdateColors();
private:
	Ui::IncomeListSubPage *m_ui;

	int m_list_size;

signals:
	void GoToCreateIncome();
	void GoToIncomeView(const Income& income);
	void IncomeClicked(const Income& income);

private slots:
	void OnIncomeClicked(IncomeListItem* income);
};
