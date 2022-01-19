#include "ListSubPage.h"
#include "ui_ListSubPage.h"

#include "Exception.h"

#include <iostream>

ListSubPage::ListSubPage(const QString& name, int id, QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListSubPage)
	, m_name(name)
	, m_id(id)
{
	m_ui->setupUi(this);
	m_ui->ListName->setText(name);
	set_list_size(0);

	connect(m_ui->AddProductButton, SIGNAL(released()), this, SLOT(OnAddProduct()));
}

void ListSubPage::AppendProduct(ListItem* product)
{
	InsertProduct(product, get_list_size());
}

void ListSubPage::InsertProduct(ListItem* product, int idx)
{
	if (get_list_size() < idx || idx < 0) {
		throw Exception("Trying to insert a widget out of range");
	}
	m_ui->ItemsLayout->insertWidget(idx, product);
	connect(product, SIGNAL(released()), this, SLOT(OnProductClicked()));
	product->set_number(idx + 1);
	set_list_size(get_list_size() + 1);
	UpdateProductNumbers(idx + 1);
}


void ListSubPage::OnAddProduct()
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

void ListSubPage::OnProductClicked()
{
	ListItem* product = qobject_cast<ListItem*>(sender());
	if (!product) {
		throw Exception("Failed to get caller object pointer");
	}

	// adding new page to stackedWidget
	ProductPage* product_page = new ProductPage;
	product_page->Setup(product->get_name()
						  , product->get_id()
						  , product->get_buy_until()
						  , product->get_price()
						  , product->get_is_purchased());

	m_ui->stackedWidget->addWidget(product_page);
	m_ui->stackedWidget->setCurrentIndex(1);
	// no use in creating some constants here
	// because it's temporary page that will be deleted in case of exit from her (GoBackButton)
}

ListItem* ListSubPage::SafeGetProduct(int idx)
{
	QLayoutItem *layout = m_ui->ItemsLayout->itemAt(idx);
	if (!layout) {
		throw Exception("Failed to get product layout");
	}
	auto* product = qobject_cast<ListItem*>(layout->widget());
	if (!product) {
		throw Exception("Failed to get product widget pointer");
	}
	return product;
}

void ListSubPage::RemoveProduct(ListItem* product)
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

void ListSubPage::UpdateProductNumbers(int idx)
{
	while (idx < get_list_size())
	{
		auto* product = SafeGetProduct(idx);
		product->set_number(++idx);
		product->Update();
	}
}

void ListSubPage::set_list_size(int size)
{
	m_list_size = size;
	m_ui->ListSize->setText(QString("%1").arg(m_list_size));
	m_ui->ListSize->show();
}

int ListSubPage::get_list_size()
{
	return m_list_size;
}

ListSubPage::~ListSubPage()
{
	delete m_ui;
}
