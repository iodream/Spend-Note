#include "ProductsSubPage.h"
#include "ui_ProductsSubPage.h"

#include "Exception.h"

#include "View/MainPage/MainPage.h"

ProductsSubPage::ProductsSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ProductsSubPage)
{
	m_ui->setupUi(this);
	set_list_size(0);

	connect(
		m_ui->AddItemButton,
		&QPushButton::clicked,
		[this](bool ignored){ GoToCreateProduct(m_list.id); });

	connect(
		m_ui->ViewList,
		&QPushButton::released,
		this,
		&ProductsSubPage::GoToViewList);
}

void ProductsSubPage::changeEvent(QEvent* event)
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

void ProductsSubPage::AppendProduct(ProductItem* product)
{
	InsertProduct(product, get_list_size());
}

void ProductsSubPage::InsertProduct(ProductItem* product, int idx)
{
	if (get_list_size() < idx || idx < 0) {
		throw Exception("Trying to insert a widget out of range");
	}
	m_ui->ItemsLayout->insertWidget(idx, product);

	connect(
		product,
		&ProductItem::released,
		[this, product](){ OnProductClicked(product); });

	product->set_number(idx + 1);
	set_list_size(get_list_size() + 1);
	UpdateProductNumbers(idx + 1);
}

void ProductsSubPage::UpdateProductNumbers(int idx)
{
	while (idx < get_list_size())
	{
		auto* product = SafeGetProduct(idx);
		product->set_number(++idx);
		product->Update();
	}
}

void ProductsSubPage::OnProductClicked(ProductItem* product)
{
	emit ProductClicked(product->get_product());
}

ProductItem* ProductsSubPage::SafeGetProduct(int idx)
{
	QLayoutItem *layout = m_ui->ItemsLayout->itemAt(idx);
	if (!layout) {
		throw Exception("Failed to get product layout");
	}
	auto* product = qobject_cast<ProductItem*>(layout->widget());
	if (!product) {
		throw Exception("Failed to get product widget pointer");
	}
	return product;
}

void ProductsSubPage::RemoveProduct(ProductItem* product)
{
	int idx = product->get_number() - 1;
	QLayoutItem *layout = m_ui->ItemsLayout->takeAt(idx);
	if (!layout) {
		throw Exception("Failed to get product layout");
	}

	delete layout->widget();
	delete layout;
	set_list_size(get_list_size() - 1);

	UpdateProductNumbers(idx);
}

void ProductsSubPage::set_list_size(int size)
{
	m_list_size = size;
	m_ui->ListSize->setText(QString("%1").arg(m_list_size));
	m_ui->ListSize->show();
}

int ProductsSubPage::get_list_size()
{
	return m_list_size;
}

void ProductsSubPage::set_list(List list)
{
	m_list = list;
}

List ProductsSubPage::get_list()
{
	return m_list;
}

ProductsSubPage::~ProductsSubPage()
{
	delete m_ui;
}

void ProductsSubPage::Update(
	const std::vector<Product>& products)
{
	m_ui->ListName->setText(m_list.name);
	Clear();
	for (auto it = products.begin(); it != products.end(); it++) {
		ProductItem* item = new ProductItem(*it);
		item->Update();
		AppendProduct(item);
	}
}

void ProductsSubPage::UpdateColors()
{
	for(int i=0; i<get_list_size(); i++)
	{
		auto product = SafeGetProduct(i);
		product->Update();
	}
	m_ui->frame->setStyleSheet("background-color:" + QString(MainPage::ColorSettings::COLOR_TOP_BANNER));
}

void ProductsSubPage::Clear()
{
	while (get_list_size()) {
		QLayoutItem *layout = m_ui->ItemsLayout->takeAt(0);
		if (!layout) {
			throw Exception("Failed to get product layout");
		}

		delete layout->widget();
		delete layout;
		set_list_size(get_list_size() - 1);
	}
}
