#pragma once

#include <QWidget>
#include <Entities/Entities.h>

namespace Ui {
class IncomeEditSubPage;
}

class IncomeEditSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit IncomeEditSubPage(QWidget *parent = nullptr);
	~IncomeEditSubPage();

	void FillCategoryBox(const std::vector<IncomeCategory>& income);

	IncomeCategory get_category();

private:
	Ui::IncomeEditSubPage *ui;
};

