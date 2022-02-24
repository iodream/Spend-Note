#include "StatisticSubPage.h"
#include "ui_StatisticSubPage.h"

#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QBarCategoryAxis>


StatisticSubPage::StatisticSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::StatisticSubPage)
{
	m_ui->setupUi(this);

	m_pie_percent_chart = InitChart(m_ui->PercentChart);
	m_pie_amount_chart = InitChart(m_ui->AmountChart);
	m_bar_balance_chart = InitChart(m_ui->BalanceChart);

	connect(
		m_ui->BackButton,
		&QPushButton::clicked,
		this,
		&StatisticSubPage::OnBackButtonClicked
	);

	connect(
		m_ui->ForwardButton,
		&QPushButton::clicked,
		this,
		&StatisticSubPage::OnForwardButtonClicked
	);
}

StatisticSubPage::~StatisticSubPage()
{
	delete m_ui;
}

QString StatisticSubPage::GetCategoryById(IdType id, std::vector<ProductCategory> category)
{
	for (const auto& el : category)
	{
		if(el.id == id) return el.name;
	}
	return "Unknown category";
}

QStringList StatisticSubPage::GetCategoryNames(std::vector<ProductCategory> category)
{
	QStringList list;
	for (const auto& el : category)
	{
		list.push_back(el.name);
	}
	return list;
}

void StatisticSubPage::UpdateCurrentChart()
{
	ChartChanged(m_ui->stackedWidget->currentIndex());
}


void StatisticSubPage::UpdatePieAmountChart(
		std::vector<ExpensePerCategory> stats,
		std::vector<ProductCategory> category)
{
	QPieSeries* series = new QPieSeries();

	for(const auto& el : stats)
	{
		QString lable = GetCategoryById(el.category_id, category) + " " + QString::number(el.amount);
		series->append(lable, el.amount);
	}
	series->setLabelsVisible();

	m_pie_amount_chart->removeAllSeries();
	m_pie_amount_chart->addSeries(series);
}

void StatisticSubPage::UpdateBarBalanceChart(std::vector<ExpensePerDay> stats)
{

	QBarSet* set = new QBarSet(nullptr);
	QBarSeries* series = new QBarSeries();
	QBarCategoryAxis* axis = new QBarCategoryAxis();
	QStringList list;

	for(const auto& el : stats)
	{
		*set << el.amount;
		list << el.day;
	}

	axis->append(list);
	series->append(set);
	series->setLabelsVisible();
	m_bar_balance_chart->createDefaultAxes();
	m_bar_balance_chart->setAxisX(axis, series);
	m_bar_balance_chart->removeAllSeries();
	m_bar_balance_chart->addSeries(series);
}

void StatisticSubPage::UpdatePiePercentChart(
		std::vector<ExpensePercentagePerCategory> stats,
		std::vector<ProductCategory> category)
{
	QPieSeries* series = new QPieSeries();

	for(const auto& el : stats)
	{
		QString label = GetCategoryById(el.category_id, category) + " " +QString::number(el.percentage) + "%";
		series->append(label, el.percentage);
	}

	series->setLabelsVisible();

	m_pie_percent_chart->removeAllSeries();
	m_pie_percent_chart->addSeries(series);
}

QChart* StatisticSubPage::InitChart(QLayout* layout)
{
	QChart* chart = new QChart();

	chart->legend()->hide();
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->createDefaultAxes();
	chart->setTheme(QChart::ChartThemeQt);

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	layout->addWidget(chartView);

	return chart;
}


void StatisticSubPage::OnForwardButtonClicked()
{
	int current_index = m_ui->stackedWidget->currentIndex();
	if (current_index == m_ui->stackedWidget->count() - 1)
	{
		current_index = 0;
	}
	else
	{
		current_index++;
	}
	m_ui->stackedWidget->setCurrentIndex(current_index);
	ChartChanged(current_index);
}

void StatisticSubPage::OnBackButtonClicked()
{
	int current_index = m_ui->stackedWidget->currentIndex();
	if (current_index == 0)
	{
		current_index = m_ui->stackedWidget->count() - 1;
	}
	else
	{
		current_index--;
	}
	m_ui->stackedWidget->setCurrentIndex(current_index);
	ChartChanged(current_index);
}

void StatisticSubPage::ChartChanged(int index)
{
	if (index == 0)
	{
		emit PercentChartSelected();
	}
	else if (index == 1)
	{
		emit AmountChartSelected();
	}
	else
	{
		emit BalanceChartSelected();
	}
}

