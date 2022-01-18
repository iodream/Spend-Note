#include "ListPage.h"
#include "ui_ListPage.h"

#include "Exception.h"

#include <iostream>

ListPage::ListPage(QString name, int id, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ListPage)
	, m_name(name)
	, m_id(id)
{
	ui->setupUi(this);
	ui->ListName->setText(name);
	set_list_size(0);

	connect(ui->AddProductButton, SIGNAL(released()), this, SLOT(OnAddProduct()));
}

void ListPage::AppendProduct(ListItem* product)
{
	InsertProduct(product, get_list_size());
}

void ListPage::InsertProduct(ListItem* product, int idx)
{
	if (get_list_size() < idx || idx < 0) {
		throw Exception("Trying to insert a widget out of range");
	}
	ui->ItemsLayout->insertWidget(idx, product);
	connect(product, SIGNAL(released()), this, SLOT(OnProductClicked()));
	product->set_number(idx + 1);
	set_list_size(get_list_size() + 1);
	UpdateProductNumbers(idx + 1);
}


void ListPage::OnAddProduct()
{
	int id = get_list_size();
	ListItem* product = new ListItem(id);
	product->set_name(QString("product %1").arg(id));
	product->set_buy_until(QString("date? Ok it is %1").arg(id));
	product->set_price(QString("price"));
	product->set_is_purchased(false);
	product->Update();
//	AppendProduct(product);
	InsertProduct(product, 0);
}

void ListPage::OnProductClicked()
{
	ListItem* product = qobject_cast<ListItem*>(sender());
	if (!product) {
		throw Exception("Failed to get caller object pointer");
	}

	RemoveProduct(product);
}

ListItem* ListPage::SafeGetProduct(int idx)
{
	QLayoutItem *layout = ui->ItemsLayout->itemAt(idx);
	if (!layout) {
		throw Exception("Failed to get product layout");
	}
	auto* product = qobject_cast<ListItem*>(layout->widget());
	if (!product) {
		throw Exception("Failed to get product widget pointer");
	}
	return product;
}

void ListPage::RemoveProduct(ListItem* product)
{
	int idx = product->get_number() - 1;
	QLayoutItem *layout = ui->ItemsLayout->takeAt(idx);
	if (!layout) {
		throw Exception("Failed to get product layout");
	}

	delete layout->widget();
	delete layout;
	set_list_size(get_list_size() - 1);

	UpdateProductNumbers(idx);
}

void ListPage::UpdateProductNumbers(int idx)
{
	while (idx < get_list_size())
	{
		auto* product = SafeGetProduct(idx);
		product->set_number(++idx);
		product->Update();
	}
}

void ListPage::set_list_size(int size)
{
	m_list_size = size;
	ui->ListSize->setText(QString("%1").arg(m_list_size));
	ui->ListSize->show();
}

int ListPage::get_list_size()
{
	return m_list_size;
}

ListPage::~ListPage()
{
	delete ui;
}
