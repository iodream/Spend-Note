#include "StatisticSubPage.h"
#include "ui_StatisticSubPage.h"

#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

StatisticSubPage::StatisticSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::StatisticSubPage)
{
	m_ui->setupUi(this);
	FormingChart();
}

StatisticSubPage::~StatisticSubPage()
{
	delete m_ui;
}

void StatisticSubPage::FormingChart()
{
	QPieSeries *series = new QPieSeries();
	series->setHoleSize(0.35);

	std::vector<QPieSlice*> slices;

	//TEST
	struct Pie
	{
		QString name;
		int number;
	};

	Pie pie1{"Products 15%", 15};
	Pie pie2{"Rent flat 20%", 20};
	Pie pie3{"Helth 10%", 10};
	Pie pie4{"Entertainment 30%", 30};
	Pie pie5{"Bills 15%", 15};
	Pie pie6{"Subscription 10%", 10};
	std::vector<Pie> pie;


	pie.push_back(pie1);
	pie.push_back(pie2);
	pie.push_back(pie3);
	pie.push_back(pie4);
	pie.push_back(pie5);
	pie.push_back(pie6);
	//================================

	for(const auto& el : pie)
	{
		slices.push_back(series->append(el.name, el.number));
	}

	QChart *chart = new QChart();

	chart->legend()->hide();
	chart->addSeries(series);
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->createDefaultAxes();
	chart->setTitle("Spendings");
	chart->setTheme(QChart::ChartThemeQt);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setParent(m_ui->verticalFrame);

}

void StatisticSubPage::OnForwardButtonClicked()
{
	int current_index = m_ui->stackedWidget->currentIndex();
	m_ui->stackedWidget->setCurrentIndex(++current_index);
}


void StatisticSubPage::OnBackButtonClicked()
{
	int current_index = m_ui->stackedWidget->currentIndex();
	m_ui->stackedWidget->setCurrentIndex(--current_index);
}

