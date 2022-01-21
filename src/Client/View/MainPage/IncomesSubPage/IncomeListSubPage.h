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
	using IdType = int;

	explicit IncomeListSubPage(IdType id, QWidget *parent=nullptr);
	~IncomeListSubPage();

	void AppendIncome(IncomeListItem* income);
	void InsertIncome(IncomeListItem* income, int idx);
	void RemoveIncome(IncomeListItem* income);

	void UpdateNumbers(int idx);

	IncomeListItem* SafeGetIncome(int idx);
private:
	void set_list_size(int size);
	int get_list_size();

	Ui::IncomeListSubPage *m_ui;

	IdType m_id;

	int m_list_size;

private slots:
	// temporary plugs, should be reimplemented
	void OnAddIncome();
	void OnIncomeClicked();
};
