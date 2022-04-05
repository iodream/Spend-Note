#pragma once

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QStackedWidget>

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

	QString GetProductCategoryById(IdType id, const std::vector<ProductCategory>& category);
	QStringList GetProductCategoryNames(const std::vector<ProductCategory>& category);

	QString GetIncomeCategoryById(IdType id, const std::vector<IncomeCategory>& category);
	QStringList GetIncomeCategoryNames(const std::vector<IncomeCategory>& category);

	void UpdateCurrentChart();

	void UpdateProductPiePercentChart(const std::vector<ExpensePercentagePerCategory>& stats, const std::vector<ProductCategory>& category);
	void UpdateProductPieAmountChart(const std::vector<ExpensePerCategory>& stats, const std::vector<ProductCategory>& category);
	void UpdateBarBalanceChart(const std::vector<ExpensePerDay>& stats);

	void UpdateIncomePiePercentChart(const std::vector<ExpensePercentagePerCategory>& stats, const std::vector<IncomeCategory>& category);
	void UpdateIncomePieAmountChart(const std::vector<ExpensePerCategory>& stats, const std::vector<IncomeCategory>& category);
	void UpdateBarIncomeChart(const std::vector<ExpensePerDay>& stats);

	void ChangePageToNext(QStackedWidget& widget);
	void ChangePageToPrevious(QStackedWidget& widget);

	void ShowEmptyMessage();
	void HideEmptyMessage();

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
