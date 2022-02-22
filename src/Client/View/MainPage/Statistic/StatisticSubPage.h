#pragma once

#include <QWidget>

namespace Ui {
class StatisticSubPage;
}

class StatisticSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit StatisticSubPage(QWidget *parent = nullptr);
	~StatisticSubPage();

	void FormingChart(/*vector of enteties*/);

private slots:
	void OnForwardButtonClicked();
	void OnBackButtonClicked();

private:
	Ui::StatisticSubPage *m_ui;
};
