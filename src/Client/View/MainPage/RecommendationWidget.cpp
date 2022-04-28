#include "RecommendationWidget.h"
#include "ui_RecommendationWidget.h"
#include <QPainter>
#include <QStyleOption>

RecommendationWidget::RecommendationWidget(QWidget *parent)
	: QWidget(parent)
	, m_list_size(0)
	, m_ui(new Ui::RecommendationWidget)
{
	setAttribute(Qt::WA_Hover, true);	// needed for hover effect
	m_ui->setupUi(this);

	connect(
			m_ui->close_button,
			&QPushButton::released,
			this,
			[this](){emit(RecommendationClosed());}
				);
}

RecommendationWidget::~RecommendationWidget()
{
	delete m_ui;
}

void RecommendationWidget::AppendItem(RecommendationItem* Item)
{
	InsertItem(Item, GetListSize());
}

void RecommendationWidget::InsertItem(RecommendationItem* Item, int idx)
{
	m_ui->Items->insertWidget(idx, Item);
	Item->SetNumber(idx + 1);
	SetListSize(GetListSize() + 1);
}

void RecommendationWidget::enterEvent(QEnterEvent * event)
{
	setStyleSheet("background-color:rgba(242, 171, 17, 100%)");
	m_ui->close_button->setFlat(false);
	m_ui->pushButton->setFlat(false);
	QWidget::enterEvent(event);
}

void RecommendationWidget::leaveEvent(QEvent * event)
{
	m_ui->close_button->setFlat(true);
	m_ui->pushButton->setFlat(true);
	setStyleSheet(QString("background-color:rgba(242, 171, 17, %1%)").arg(Transparency));
	QWidget::leaveEvent(event);
}


int RecommendationWidget::GetListSize()
{
	return m_list_size;
}

void RecommendationWidget::SetListSize(int size)
{
	m_list_size = size;
}
