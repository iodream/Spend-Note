#include "RecommendationWidget.h"
#include "ui_RecommendationWidget.h"

RecommendationWidget::RecommendationWidget(QString name, QWidget *parent)
	: QPushButton(parent)
	, m_ui(new Ui::RecommendationWidget)
{
	m_ui->setupUi(this);
}

RecommendationWidget::~RecommendationWidget()
{
	delete m_ui;
}
