#pragma once

#include <QWidget>
#include <Entities/Entities.h>

#include "View/Constants.h"

namespace Ui {
class PeriodicIncomeEditSubPage;
}

class PeriodicIncomeEditSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit PeriodicIncomeEditSubPage(QWidget *parent = nullptr);
	~PeriodicIncomeEditSubPage();
	void Update(const Income& income);
	void SetMinimumDate(const QDate&);

	const Income& get_income();
	void set_income(const Income& income);

signals:
	void UpdateIncome();
	void AddIncomeCategory(IncomeCategory);
	void UpdateCategories();

public slots:
	void OnEditIncome();
	void FillCategoryBox(const std::vector<IncomeCategory>& income);
	void OnNewCategoryPushed();
	void OnNewCategorySaved();

	IncomeCategory get_category();

private:
	Ui::PeriodicIncomeEditSubPage *m_ui;
	Income m_income;
};

