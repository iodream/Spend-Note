#pragma once

#include <QWidget>
#include <Entities/Entities.h>

#include "View/Constants.h"

namespace Ui {
class IncomeEditSubPage;
}

class IncomeEditSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit IncomeEditSubPage(QWidget *parent = nullptr);
	~IncomeEditSubPage();
	void Update(const Income& income);
	void SetMinimumDate(const QDate&);

	const Income& get_income();
	void set_income(const Income& income);
	void changeEvent(QEvent* event);

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
	Ui::IncomeEditSubPage *ui;
	Income m_income;
};

