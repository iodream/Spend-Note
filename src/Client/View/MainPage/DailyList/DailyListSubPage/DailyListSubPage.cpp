#include "DailyListSubPage.h"
#include "ui_DailyListSubPage.h"

#include "Exception.h"

#include "View/MainPage/MainPage.h"

DailyListSubPage::DailyListSubPage(QWidget* parent)
	: QWidget(parent)
	, m_ui(new Ui::DailyListSubPage)
{
	m_ui->setupUi(this);
	set_list_size(0);
}

void DailyListSubPage::changeEvent(QEvent* event)
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

void DailyListSubPage::AppendProduct(ProductItem *product)
{
	InsertProduct(product, get_list_size());
}

void DailyListSubPage::InsertProduct(ProductItem *product, int idx)
{
	if (get_list_size() < idx || idx < 0) {
		throw Exception("Trying to insert a widget out of range");
	}
	m_ui->ItemsLayout_4->insertWidget(idx, product);

	connect(
		product,
		&ProductItem::clicked,
		[this, product](){ OnProductClicked(product); });

	product->set_number(idx + 1);
	set_list_size(get_list_size() + 1);
	UpdateNumbers(idx + 1);
}

void DailyListSubPage::set_list_size(int size)
{
	m_list_size = size;	
}

int DailyListSubPage::get_list_size()
{
	return m_list_size;
}

void DailyListSubPage::UpdateNumbers(int idx)
{
	while (idx < get_list_size())
	{
		auto* product = SafeGetProduct(idx);
		product->set_number(++idx);
		product->Update();
	}
}

void DailyListSubPage::Update(const std::vector<Product>& products)
{
	Clear();
	for (auto it = products.begin(); it != products.end(); it++) {
		ProductItem* item = new ProductItem(*it);
		item->Update();
		AppendProduct(item);
	}
}

void DailyListSubPage::UpdateColors()
{
	m_ui->verticalFrame->setStyleSheet("background-color:" + QString(MainPage::ColorSettings::COLOR_TOP_BANNER));
}


ProductItem* DailyListSubPage::SafeGetProduct(int idx)
{
	QLayoutItem *layout = m_ui->ItemsLayout_4->itemAt(idx);
	if (!layout) {
		throw Exception("Failed to get income layout");
	}
	auto* product = qobject_cast<ProductItem*>(layout->widget());
	if (!product) {
		throw Exception("Failed to get income widget pointer");
	}
	return product;
}

void DailyListSubPage::Clear()
{
	while (get_list_size()) {
		QLayoutItem *layout = m_ui->ItemsLayout_4->takeAt(0);
		if (!layout) {
			throw Exception("Failed to get product layout");
		}

		delete layout->widget();
		delete layout;
		set_list_size(get_list_size() - 1);
	}
}

void DailyListSubPage::OnProductClicked(ProductItem* product)
{
	emit GoToProductView(product->get_product());
}


DailyListSubPage::~DailyListSubPage()
{
	delete m_ui;
}
