#include "RecommendationWidget.h"
#include "ui_RecommendationWidget.h"

RecommendationWidget::RecommendationWidget(QWidget *parent)
	: QWidget(parent)
	, m_list_size(0)
	, m_ui(new Ui::RecommendationWidget)
{
	m_ui->setupUi(this);
	setAttribute(Qt::WA_StyledBackground, true);

	connect(m_ui->close_button,
			&QPushButton::released,
			this,
			[this](){ emit RecommendationClosed(); });
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

int RecommendationWidget::GetListSize()
{
	return m_list_size;
}

void RecommendationWidget::SetListSize(int size)
{
	m_list_size = size;
}
