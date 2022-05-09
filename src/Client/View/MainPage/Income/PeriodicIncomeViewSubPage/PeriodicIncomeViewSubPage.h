#pragma once

#include <QString>
#include <QWidget>

#include "Entities/Entities.h"
#include "View/Constants.h"

namespace Ui {
class PeriodicIncomeViewSubPage;
}

class PeriodicIncomeViewSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit PeriodicIncomeViewSubPage(QWidget *parent=nullptr);
	~PeriodicIncomeViewSubPage();

	void Update(const Income& income);

	void set_income(const Income& income);
	Income get_income() const;

signals:
	void GoBack(int n=1);
	void GoToEditIncome(Income income);
	void DeleteIncome(Income income);

private:
	Ui::PeriodicIncomeViewSubPage *m_ui;
	Income m_income;
};
