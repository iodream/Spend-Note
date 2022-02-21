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

signals:
	void CreateIncome(Income& income);
public slots:
	void OnCreateIncome();
private:
	Ui::IncomeCreateSubPage *ui;
};

