#pragma once

#include <QWidget>

namespace Ui {
class DailyListSubPage;
}

class DailyListSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit DailyListSubPage(QWidget *parent = nullptr);
	~DailyListSubPage();

private:
	Ui::DailyListSubPage *ui;
};

