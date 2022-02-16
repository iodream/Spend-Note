#pragma once

#include <QWidget>

namespace Ui {
class IncomeCreateSubPage;
}

class IncomeCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit IncomeCreateSubPage(QWidget *parent = nullptr);
	~IncomeCreateSubPage();

private:
	Ui::IncomeCreateSubPage *ui;
};

