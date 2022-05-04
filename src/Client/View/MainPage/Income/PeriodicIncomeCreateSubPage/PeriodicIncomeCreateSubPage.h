#pragma once

#include <QWidget>
#include <Entities/Entities.h>

namespace Ui {
class PeriodicIncomeCreateSubPage;
}

class PeriodicIncomeCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit PeriodicIncomeCreateSubPage(QWidget *parent = nullptr);
	void SetMinimumDate(const QDate& date);
	~PeriodicIncomeCreateSubPage();
	void Clear();

signals:
	void CreateIncome(Income& Income);
	void AddIncomeCategory(IncomeCategory);
	void UpdateCategories();

public slots:
	void OnCreateIncome();
	void FillCategoryBox(const std::vector<IncomeCategory>& Income);
	void OnNewCategoryPushed();
	void OnNewCategorySaved();

	IncomeCategory get_category();

private:
	Ui::PeriodicIncomeCreateSubPage *ui;
};

