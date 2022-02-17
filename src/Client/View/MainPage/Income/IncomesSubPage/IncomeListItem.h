#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>

#include "Client/Entities/Entities.h"

namespace Ui {
class IncomeListItem;
}

class IncomeListItem : public QPushButton
{
	Q_OBJECT

public:
	using IdType = int;

	explicit IncomeListItem(Income income, QWidget *parent = nullptr);
	~IncomeListItem();

	void Update();

	Income get_income() const { return m_income; };

	void set_number(int number);
	int get_number();

	QString get_color();

private:
	void UpdateColor();

	Income m_income;

	int m_number{1};
	QString m_color;

	Ui::IncomeListItem *m_ui;
};
