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

signals:
	void CreateIncome(Income& income);
public slots:
	void OnCreateIncome();
private:
	Ui::IncomeCreateSubPage *ui;
};

