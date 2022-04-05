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
	m_pie_income_amount_chart = InitChart(m_ui->PercentIncomeChart);
	m_pie_income_amount_chart = InitChart(m_ui->AmountIncomeChart);
	m_bar_income_chart = InitChart(m_ui->BarIncomeChart);

	m_ui->tabWidget->setTabText(0, "Outcomes");
	m_ui->tabWidget->setTabText(1, "Incomes");

	m_ui->tabWidget->setCurrentIndex(0);

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

QString StatisticSubPage::GetProductCategoryById(IdType id, std::vector<ProductCategory> category)
{
	for (const auto& el : category)
	{
		if(el.id == id) return el.name;
	}
	return "Unknown category";
}

QStringList StatisticSubPage::GetProductCategoryNames(std::vector<ProductCategory> category)
{
	QStringList list;
	for (const auto& el : category)
	{
		list.push_back(el.name);
	}
	return list;
}

QString StatisticSubPage::GetIncomeCategoryById(IdType id, std::vector<IncomeCategory> category)
{
	for (const auto& el : category)
	{
		if(el.id == id) return el.name;
	}
	return "Unknown category";
}

QStringList StatisticSubPage::GetIncomeCategoryNames(std::vector<IncomeCategory> category)
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
	if(m_ui->tabWidget->currentIndex() == 0)
	{
		ChartChanged(m_ui->stackedWidget->currentIndex());
	}
	else if(m_ui->tabWidget->currentIndex() == 1)
	{
		ChartChanged(m_ui->stackedWidget_2->currentIndex());
	}
}


void StatisticSubPage::UpdateProductPieAmountChart(
		std::vector<ExpensePerCategory> stats,
		std::vector<ProductCategory> category)
{
	if (stats.empty())
	{
		ShowEmptyMessage();
	}
	else
	{
		HideEmptyMessage();

		QPieSeries* series = new QPieSeries();

		for(const auto& el : stats)
		{
			QString lable = GetProductCategoryById(el.category_id, category) + " " + QString::number(el.amount) + "$";
			series->append(lable, el.amount);
		}

		series->setLabelsVisible();

		m_pie_amount_chart->removeAllSeries();
		m_pie_amount_chart->addSeries(series);
	}
}

void StatisticSubPage::UpdateBarBalanceChart(std::vector<ExpensePerDay> stats)
{
	if (stats.empty())
	{
		ShowEmptyMessage();
	}
	else
	{
		HideEmptyMessage();

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
}

void StatisticSubPage::UpdateIncomePiePercentChart(
		std::vector<ExpensePercentagePerCategory> stats,
		std::vector<IncomeCategory> category)
{
	if (stats.empty())
	{
		ShowEmptyMessage();
	}
	else
	{
		HideEmptyMessage();

		QPieSeries* series = new QPieSeries();

		for(const auto& el : stats)
		{
			QString label = GetIncomeCategoryById(el.category_id, category) + " " +QString::number(el.percentage) + "%";
			series->append(label, el.percentage);
		}

		series->setLabelsVisible();
		series->setHoleSize(0.35);

		m_pie_income_persent_chart->removeAllSeries();
		m_pie_income_persent_chart->addSeries(series);
	}
}

void StatisticSubPage::UpdateIncomePieAmountChart(
		std::vector<ExpensePerCategory> stats,
		std::vector<IncomeCategory> category)
{
	if (stats.empty())
	{
		ShowEmptyMessage();
	}
	else
	{
		HideEmptyMessage();

		QPieSeries* series = new QPieSeries();

		for(const auto& el : stats)
		{
			QString lable = GetIncomeCategoryById(el.category_id, category) + " " + QString::number(el.amount) + "$";
			series->append(lable, el.amount);
		}

		series->setLabelsVisible();

		m_pie_income_amount_chart->removeAllSeries();
		m_pie_income_amount_chart->addSeries(series);
	}
}

void StatisticSubPage::UpdateBarIncomeChart(std::vector<ExpensePerDay> stats)
{
	if (stats.empty())
	{
		ShowEmptyMessage();
	}
	else
	{
		HideEmptyMessage();

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
		m_bar_income_chart->createDefaultAxes();
		m_bar_income_chart->setAxisX(axis, series);
		m_bar_income_chart->removeAllSeries();
		m_bar_income_chart->addSeries(series);
	}
}

void StatisticSubPage::UpdateProductPiePercentChart(
		std::vector<ExpensePercentagePerCategory> stats,
		std::vector<ProductCategory> category)
{
	if (stats.empty())
	{
		ShowEmptyMessage();
	}
	else
	{
		HideEmptyMessage();

		QPieSeries* series = new QPieSeries();

		for(const auto& el : stats)
		{
			QString label = GetProductCategoryById(el.category_id, category) + " " +QString::number(el.percentage) + "%";
			series->append(label, el.percentage);
		}

		series->setLabelsVisible();
		series->setHoleSize(0.35);

		m_pie_percent_chart->removeAllSeries();
		m_pie_percent_chart->addSeries(series);
	}
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
	if(m_ui->tabWidget->currentIndex() == 0)
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
	else if(m_ui->tabWidget->currentIndex() == 1)
	{
		int current_index = m_ui->stackedWidget_2->currentIndex();
		if (current_index == m_ui->stackedWidget_2->count() - 1)
		{
			current_index = 0;
		}
		else
		{
			current_index++;
		}
		m_ui->stackedWidget_2->setCurrentIndex(current_index);
		ChartChanged(current_index);
	}
}

void StatisticSubPage::OnBackButtonClicked()
{
	if(m_ui->tabWidget->currentIndex() == 0)
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
	else if(m_ui->tabWidget->currentIndex() == 1)
	{
		int current_index = m_ui->stackedWidget_2->currentIndex();
		if (current_index == 0)
		{
			current_index = m_ui->stackedWidget_2->count() - 1;
		}
		else
		{
			current_index--;
		}
		m_ui->stackedWidget_2->setCurrentIndex(current_index);
		ChartChanged(current_index);
	}
}

void StatisticSubPage::ChartChanged(int index)
{
	switch (m_ui->tabWidget->currentIndex())
	{
	case 0:
	{
		if (index == 0)
		{
			emit PercentProductChartSelected();
		}
		else if (index == 1)
		{
			emit AmountProductChartSelected();
		}
		else
		{
			emit BalanceChartSelected();
		}
	}
	case 1:
	{
		if (index == 0)
		{
			emit PercentIncomeChartSelected();
		}
		else if (index == 1)
		{
			emit AmountIncomeChartSelected();
		}
		else
		{
			emit IncomeChartSelected();
		}
	}
	}

}

void StatisticSubPage::ShowEmptyMessage()
{
	if(m_ui->tabWidget->currentIndex() == 0)
	{
		switch (m_ui->stackedWidget->currentIndex())
		{
		case 0:
		{
			m_pie_percent_chart->hide();
			m_ui->NotEnoughData1->show();
			break;
		}
		case 1:
		{
			m_pie_amount_chart->hide();
			m_ui->NotEnoughData2->show();
			break;
		}
		case 2:
		{
			m_bar_balance_chart->hide();
			m_ui->NotEnoughData3->show();
			break;
		}
		}
	}
	else if(m_ui->tabWidget->currentIndex() == 1)
	{
		switch (m_ui->stackedWidget_2->currentIndex())
		{
		case 0:
		{
			m_pie_income_amount_chart->hide();
			m_ui->NotEnoughData4->show();
			break;
		}
		case 1:
		{
			m_pie_income_amount_chart->hide();
			m_ui->NotEnoughData5->show();
			break;
		}
		case 2:
		{
			m_bar_income_chart->hide();
			m_ui->NotEnoughData6->show();
			break;
		}
		}
	}
}

void StatisticSubPage::HideEmptyMessage()
{
	if(m_ui->tabWidget->currentIndex() == 0)
	{
		switch (m_ui->stackedWidget->currentIndex())
		{
		case 0:
		{
			m_ui->NotEnoughData1->hide();
			m_pie_percent_chart->show();
			break;
		}
		case 1:
		{
			m_ui->NotEnoughData2->hide();
			m_pie_amount_chart->show();
			break;
		}
		case 2:
		{
			m_ui->NotEnoughData3->hide();
			m_bar_balance_chart->show();
			break;
		}
		}
	}
	else if(m_ui->tabWidget->currentIndex() == 1)
	{
		switch (m_ui->stackedWidget_2->currentIndex())
		{
		case 0:
		{
			m_ui->NotEnoughData4->hide();
			m_pie_income_amount_chart->show();
			break;
		}
		case 1:
		{
			m_ui->NotEnoughData5->hide();
			m_pie_income_amount_chart->show();
			break;
		}
		case 2:
		{
			m_ui->NotEnoughData6->hide();
			m_bar_income_chart->show();
			break;
		}
		}
	}
}

