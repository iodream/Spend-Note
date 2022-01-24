#include "ProductsSubPage.h"
#include "ui_ProductsSubPage.h"

#include "Exception.h"

#include <iostream>

ProductsSubPage::ProductsSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ProductsSubPage)
{
	m_ui->setupUi(this);
//	m_ui->ListName->setText(name);
	set_list_size(0);
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
	connect(product, &ProductItem::released, [this, product](){ OnProductClicked(product); });
	product->set_number(idx + 1);
	set_list_size(get_list_size() + 1);
	UpdateProductNumbers(idx + 1);
}

//void ProductsSubPage::OnAddProduct()
//{
//	int id = get_list_size();
//	ProductItem* product = new ProductItem(id);
//	product->set_name(QString("product %1").arg(id));
//	product->set_buy_until(QString("date? Ok it is %1").arg(id));
//	product->set_price(QString("price"));
//	product->set_is_purchased(false);
//	product->Update();
////	AppendProduct(product);
//}

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

void ProductsSubPage::UpdateProductNumbers(int idx)
{
	while (idx < get_list_size())
	{
		auto* product = SafeGetProduct(idx);
		product->set_number(++idx);
		product->Update();
	}
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

ProductsSubPage::~ProductsSubPage()
{
	delete m_ui;
}
