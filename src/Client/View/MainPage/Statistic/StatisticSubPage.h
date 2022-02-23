#pragma once

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

#include "Entities/Entities.h"

namespace Ui {
class StatisticSubPage;
}

class StatisticSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit StatisticSubPage(QWidget *parent = nullptr);
	~StatisticSubPage();

	QString GetCategoryById(IdType id, std::vector<ProductCategory> category);
	QStringList GetCategoryNames(std::vector<ProductCategory> category);

	void UpdatePiePercentChart(std::vector<ExpensePercentagePerCategory> stats, std::vector<ProductCategory> category);
	void UpdatePieAmountChart(std::vector<ExpensePerCategory> stats, std::vector<ProductCategory> category);
	void UpdateBarBalanceChart(std::vector<ExpensePerDay> stats);

	QChart* InitPieChart(QFrame* frame);
	QChart* InitBarChart(QFrame* frame);

private slots:
	void OnForwardButtonClicked();
	void OnBackButtonClicked();

private:
	Ui::StatisticSubPage *m_ui;
	QChart* m_pie_percent_chart;
	QChart* m_pie_amount_chart;
	QChart* m_bar_balance_chart;

};
