#include "RecommendationWidget.h"
#include "ui_RecommendationWidget.h"
#include <stdexcept>
#include "View/MainPage/MainPage.h"

RecommendationWidget::RecommendationWidget(QWidget *parent)
	: QWidget(parent)
	, m_list_size(0)
	, bClosed(false)
	, m_ui(new Ui::RecommendationWidget)
{
	m_ui->setupUi(this);
	setAttribute(Qt::WA_StyledBackground, true);
	setStyleSheet("background-color: " + MainPage::ColorSettings::RECOMMENDATION);
	connect(m_ui->close_button,
			&QPushButton::released,
			this,
			[this](){ bClosed = true; emit RecommendationClosed(); });
}

RecommendationWidget::~RecommendationWidget()
{
	delete m_ui;
}

void RecommendationWidget::AppendProduct(ProductItem* Item)
{
	InsertProduct(Item, GetListSize());
}

void RecommendationWidget::RemoveProduct()
{
	QLayoutItem *layout = m_ui->Items->takeAt(0);
	if (!layout) {
		throw std::runtime_error("Failed to get list layout");
	}

	delete layout->widget();
	delete layout;
	SetListSize(0);
}

void RecommendationWidget::InsertProduct(ProductItem *product, int idx)
{
	product->SetText("");
	product->HideCheck();
	if (GetListSize() < idx || idx < 0) {
		throw std::runtime_error("Trying to insert a widget out of range");
	}

	m_ui->Items->insertWidget(idx, product);

	connect(
		product,
		&ProductItem::clicked,
		[this, product](){ OnProductClicked(product); });

	product->set_number(idx + 1);
	SetListSize(GetListSize() + 1);
}
int RecommendationWidget::GetListSize()
{
	return m_list_size;
}

void RecommendationWidget::changeEvent(QEvent* event)
{
	if(event)
	{
		switch(event->type())
		{
		case QEvent::LanguageChange:
			m_ui->retranslateUi(this);
		}

		QWidget::changeEvent(event);
	}
}

void RecommendationWidget::SetListSize(int size)
{
	m_list_size = size;
}
ProductItem* RecommendationWidget::SafeGetProduct(int idx)
{
	QLayoutItem *layout = m_ui->Items->itemAt(idx);
	if (!layout) {
		throw std::runtime_error("Failed to get recommended item layout");
	}
	auto* product = qobject_cast<ProductItem*>(layout->widget());
	if (!product) {
		throw std::runtime_error("Failed to get recommended item widget pointer");
	}
	return product;
}

void RecommendationWidget::Clear()
{
	while (GetListSize()) {
		QLayoutItem *layout = m_ui->Items->takeAt(0);
		if (!layout) {
			throw std::runtime_error("Failed to get product layout");
		}

		delete layout->widget();
		delete layout;
		SetListSize(GetListSize() - 1);
	}
}

void RecommendationWidget::OnProductClicked(ProductItem* product)
{
	emit GoToProductView(product->get_product());
}
