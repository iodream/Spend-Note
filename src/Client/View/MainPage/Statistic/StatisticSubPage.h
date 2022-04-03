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

	QString GetProductCategoryById(IdType id, std::vector<ProductCategory> category);
	QStringList GetProductCategoryNames(std::vector<ProductCategory> category);

	QString GetIncomeCategoryById(IdType id, std::vector<IncomeCategory> category);
	QStringList GetIncomeCategoryNames(std::vector<IncomeCategory> category);

	void UpdateCurrentChart();

	void UpdateProductPiePercentChart(std::vector<ExpensePercentagePerCategory> stats, std::vector<ProductCategory> category);
	void UpdateProductPieAmountChart(std::vector<ExpensePerCategory> stats, std::vector<ProductCategory> category);
	void UpdateBarBalanceChart(std::vector<ExpensePerDay> stats);

	void UpdateIncomePiePercentChart(std::vector<ExpensePercentagePerCategory> stats, std::vector<IncomeCategory> category);
	void UpdateIncomePieAmountChart(std::vector<ExpensePerCategory> stats, std::vector<IncomeCategory> category);
	void UpdateBarIncomeChart(std::vector<ExpensePerDay> stats);

	void ShowEmptyMessang();
	void HideEmptyMessang();

	QChart* InitChart(QLayout* layout);
	//QChart* InitChart(QFrame* frame);

private slots:
	void OnForwardButtonClicked();
	void OnBackButtonClicked();

private:
	Ui::StatisticSubPage *m_ui;
	QChart* m_pie_percent_chart;
	QChart* m_pie_amount_chart;
	QChart* m_bar_balance_chart;
	QChart* m_pie_income_persent_chart;
	QChart* m_pie_income_amount_chart;
	QChart* m_bar_income_chart;

	void ChartChanged(int index);

signals:
	void PercentProductChartSelected();
	void AmountProductChartSelected();
	void BalanceChartSelected();
	void PercentIncomeChartSelected();
	void AmountIncomeChartSelected();
	void IncomeChartSelected();
};
