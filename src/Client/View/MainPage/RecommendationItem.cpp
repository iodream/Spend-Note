#include "RecommendationItem.h"
#include "ui_RecommendationItem.h"

RecommendationItem::RecommendationItem(QString name, QWidget *parent)
	: QPushButton(parent)
	, m_ui(new Ui::RecommendationItem)
	, m_name(name)
{
	m_ui->setupUi(this);
	setAttribute(Qt::WA_StyledBackground, true);

	Update();
}

RecommendationItem::~RecommendationItem()
{
	delete m_ui;
}

void RecommendationItem::Update()
{
	m_ui->ListName->setText(m_name);
	m_ui->Holder->show();
}

void RecommendationItem::SetNumber(int number)
{
	m_number = number;
	m_ui->Number->setText(QString("%1").arg(m_number));
	Update();
}

