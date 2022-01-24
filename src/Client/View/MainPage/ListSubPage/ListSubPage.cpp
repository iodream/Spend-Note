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

	connect(
		m_ui->AddProductButton,
		SIGNAL(released()),
		this,
		SLOT(OnAddProduct()));

	connect(
		&m_product_page,
		SIGNAL(GoBack()),
		this,
		SLOT(OnGoBack()));
	connect(
		&m_list_create_page,
		SIGNAL(GoBack()),
		this,
		SLOT(OnGoBack()));
	m_ui->stackedWidget->addWidget(&m_product_page);

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
	connect(product, &ListItem::released, [this, product](){ OnProductClicked(product); });
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

void ListSubPage::SetCurrentListSubPage(ListProductsPages sub_page)
{
	m_ui->stackedWidget->setCurrentIndex(static_cast<int>(sub_page));
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

void ListSubPage::OnProductClicked(ListItem* product)
{
	m_product_page.Setup(product);
	SetCurrentListSubPage(ListProductsPages::PRODUCT);
}

void ListSubPage::OnGoBack()
{
	SetCurrentListSubPage(ListProductsPages::LISTS);
};

ListSubPage::~ListSubPage()
{
	delete m_ui;
}

void ListSubPage::on_EditList_clicked()
{
	m_ui->stackedWidget->addWidget(&m_list_create_page);
	m_ui->stackedWidget->setCurrentIndex(2);
}

