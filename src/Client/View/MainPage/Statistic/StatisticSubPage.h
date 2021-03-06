#pragma once

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QStackedWidget>

#include "Entities/Entities.h"
#include "View/Constants.h"

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

	void UpdateProductPiePercentChart(const std::vector<StatisticPercentagePerCategory>& stats, const std::vector<ProductCategory>& category);
	void UpdateProductPieAmountChart(const std::vector<StatisticPerCategory>& stats, const std::vector<ProductCategory>& category);
	void UpdateBarBalanceChart(const std::vector<StatisticPerDay>& stats);

	void UpdateIncomePiePercentChart(const std::vector<StatisticPercentagePerCategory>& stats, const std::vector<IncomeCategory>& category);
	void UpdateIncomePieAmountChart(const std::vector<StatisticPerCategory>& stats, const std::vector<IncomeCategory>& category);
	void UpdateBarIncomeChart(const std::vector<StatisticPerDay>& stats);

	void ChangePageToNext(QStackedWidget& widget);
	void ChangePageToPrevious(QStackedWidget& widget);

	void ShowEmptyMessage();
	void HideEmptyMessage();

	std::string GetCurrentRange();
	std::string GetCurrentTabName();
	std::string GetCurrentTabNameDefault();

	int GetCurrentTabIndex();

	QChart* InitChart(QLayout* layout);

	void changeEvent(QEvent* event);
private slots:
	void OnForwardButtonClicked();
	void OnBackButtonClicked();
	void OnRefreshButtonClicked();

	void OnTabChanged(int index);
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
