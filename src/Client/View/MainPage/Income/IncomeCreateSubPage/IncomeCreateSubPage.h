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
	~IncomeCreateSubPage();

	void FillCategoryBox(const std::vector<IncomeCategory>& income);

	IncomeCategory get_category();

private:
	Ui::IncomeCreateSubPage *ui;
};

