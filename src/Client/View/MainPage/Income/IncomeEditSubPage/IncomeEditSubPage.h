#pragma once

#include <QWidget>
#include "Entities/Entities.h"

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

signals:
	void UpdateIncome(Income& income);
	
public slots:
	void OnEditIncome();
private:
	Ui::IncomeEditSubPage *ui;
};

