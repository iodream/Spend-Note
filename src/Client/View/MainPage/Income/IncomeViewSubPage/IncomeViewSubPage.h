#pragma once

#include <QString>
#include <QWidget>

#include "Entities/Entities.h"
#include "View/Constants.h"

namespace Ui {
class IncomeViewSubPage;
}

class IncomeViewSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit IncomeViewSubPage(QWidget *parent=nullptr);
	~IncomeViewSubPage();

	void Update(const Income& income);

	void set_income(const Income& income);
	Income get_income() const;

signals:
	void GoBack(int n=1);
	void GoToEditIncome(Income income);
	void DeleteIncome(Income income);

private:
	Ui::IncomeViewSubPage *m_ui;
	Income m_income;
};
