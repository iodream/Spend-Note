#pragma once

#include <QWidget>
#include <Entities/Entities.h>

namespace Ui {
class IncomeCreateSubPage;
}

class IncomeCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit IncomeCreateSubPage(QWidget *parent = nullptr);
	void SetMinimumDate(const QDate& date);
	~IncomeCreateSubPage();
	void Clear();
	void changeEvent(QEvent* event);

signals:
	void CreateIncome(Income& income);
	void AddIncomeCategory(IncomeCategory);
	void UpdateCategories();

public slots:
	void OnCreateIncome();
	void FillCategoryBox(const std::vector<IncomeCategory>& income);
	void OnNewCategoryPushed();
	void OnNewCategorySaved();

	IncomeCategory get_category();

private:
	Ui::IncomeCreateSubPage *ui;
};

