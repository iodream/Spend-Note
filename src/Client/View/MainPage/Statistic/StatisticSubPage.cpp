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
	m_pie_income_persent_chart = InitChart(m_ui->PercentIncomeChart);
	m_pie_income_amount_chart = InitChart(m_ui->AmountIncomeChart);
	m_bar_income_chart = InitChart(m_ui->BarIncomeChart);

	m_ui->tabWidget->setTabText(0, tr("Outcomes"));
	m_ui->tabWidget->setTabText(1, tr("Incomes"));

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

	connect(
		m_ui->RefreshButton,
		&QPushButton::clicked,
		this,
		&StatisticSubPage::OnRefreshButtonClicked
	);

	connect(
		m_ui->tabWidget,
		&QTabWidget::currentChanged,
		this,
		&StatisticSubPage::OnTabChanged
	);


}

StatisticSubPage::~StatisticSubPage()
{
	delete m_ui;
}

void StatisticSubPage::changeEvent(QEvent* event)
{
 if(event)
 {
  switch(event->type())
  {
   case QEvent::LanguageChange:
	m_ui->retranslateUi(this);
	break;
  }

 QWidget::changeEvent(event);
 }
}

QString StatisticSubPage::GetProductCategoryById(IdType id, const std::vector<ProductCategory>& category)
{
	for (const auto& el : category)
	{
		if(el.id == id) return el.name;
	}
	return "Unknown category";
}

QStringList StatisticSubPage::GetProductCategoryNames(const std::vector<ProductCategory>& category)
{
	QStringList list;
	for (const auto& el : category)
	{
		list.push_back(el.name);
	}
	return list;
}

QString StatisticSubPage::GetIncomeCategoryById(IdType id, const std::vector<IncomeCategory>& category)
{
	for (const auto& el : category)
	{
		if(el.id == id) return el.name;
	}
	return "Unknown category";
}

QStringList StatisticSubPage::GetIncomeCategoryNames(const std::vector<IncomeCategory>& category)
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

void StatisticSubPage::UpdateBarBalanceChart(const std::vector<StatisticPerDay>& stats)
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
		const std::vector<StatisticPercentagePerCategory>& stats,
		const std::vector<IncomeCategory>& category)
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
			QString label = GetIncomeCategoryById(el.category_id, category) + " " + QString::number(el.percentage) + "%";
			series->append(label, el.percentage);
		}

		series->setLabelsVisible();
		series->setHoleSize(0.35);

		m_pie_income_persent_chart->removeAllSeries();
		m_pie_income_persent_chart->addSeries(series);
	}
}

void StatisticSubPage::UpdateIncomePieAmountChart(
		const std::vector<StatisticPerCategory>& stats,
		const std::vector<IncomeCategory>& category)
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
		series->setHoleSize(0.35);

		m_pie_income_amount_chart->removeAllSeries();
		m_pie_income_amount_chart->addSeries(series);
	}
}

void StatisticSubPage::UpdateBarIncomeChart(const std::vector<StatisticPerDay>& stats)
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

void StatisticSubPage::ChangePageToNext(QStackedWidget& widget)
{
	int current_index = widget.currentIndex();
	if (current_index == widget.count() - 1)
	{
		current_index = 0;
	}
	else
	{
		current_index++;
	}
	widget.setCurrentIndex(current_index);
	ChartChanged(current_index);
}

void StatisticSubPage::ChangePageToPrevious(QStackedWidget& widget)
{
	int current_index = widget.currentIndex();
	if (current_index == 0)
	{
		current_index = widget.count() - 1;
	}
	else
	{
		current_index--;
	}
	widget.setCurrentIndex(current_index);
	ChartChanged(current_index);
}

void StatisticSubPage::UpdateProductPieAmountChart(
	const std::vector<StatisticPerCategory>& stats,
	const std::vector<ProductCategory>& category)
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
	  QString label = GetProductCategoryById(el.category_id, category) + " " + QString::number(el.amount) + "$";
	  series->append(label, el.amount);
	}

	series->setLabelsVisible();
	series->setHoleSize(0.35);

	m_pie_amount_chart->removeAllSeries();
	m_pie_amount_chart->addSeries(series);
  }
}

void StatisticSubPage::UpdateProductPiePercentChart(
		const std::vector<StatisticPercentagePerCategory>& stats,
		const std::vector<ProductCategory>& category)
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
			QString label = GetProductCategoryById(el.category_id, category) + " " + QString::number(el.percentage) + "%";
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
		ChangePageToNext(*m_ui->stackedWidget);
	}
	else if(m_ui->tabWidget->currentIndex() == 1)
	{
		ChangePageToNext(*m_ui->stackedWidget_2);
	}
}

void StatisticSubPage::OnBackButtonClicked()
{
	if(m_ui->tabWidget->currentIndex() == 0)
	{
		ChangePageToPrevious(*m_ui->stackedWidget);
	}
	else if(m_ui->tabWidget->currentIndex() == 1)
	{
		ChangePageToPrevious(*m_ui->stackedWidget_2);
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


std::string StatisticSubPage::GetCurrentRange()
{
	return m_ui->periods->currentText().toStdString();
}

std::string StatisticSubPage::GetCurrentTabName()
{
	if(!m_ui->tabWidget->currentIndex()) // if indedx == 0
		return STATISTIC_EXPENSES;
	return STATISTIC_INCOMES;
}

void StatisticSubPage::OnRefreshButtonClicked()
{
	UpdateCurrentChart();
}

void StatisticSubPage::OnTabChanged(int index)
{
	if(index)
		emit OnRefreshButtonClicked();
}

