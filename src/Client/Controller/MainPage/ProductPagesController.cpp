#include "ProductPagesController.h"

#include "Models/Product/GetProductsModel.h"
#include "Models/Product/AddProductModel.h"

#include "Net/Constants.h"

ProductPagesController::ProductPagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	ProductsSubPage& products_page,
	ProductViewSubPage& view_page,
	ProductCreateSubPage& create_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_products_page{products_page}
	, m_view_page{view_page}
	, m_create_page{create_page}
{
	ConnectProductsPage();
	ConnectViewPage();
	ConnectCreatePage();
}

bool ProductPagesController::UpdateProductsPage(PageData data)
{
	if (!data.canConvert<List>()) {
		return UpdateProductsPage();
	}
	return UpdateProductsPage(qvariant_cast<List>(data));
}

bool ProductPagesController::UpdateViewProductSubPage(PageData data)
{
	if (!data.canConvert<Product>()) {
		return false;
		//return m_product_pages_controller->UpdateListPage();
	}
	return UpdateViewPage(qvariant_cast<Product>(data));
}



void ProductPagesController::ConnectProductsPage()
{
	connect(
		&m_products_page,
		&ProductsSubPage::ProductClicked,
		this,
		&ProductPagesController::OnProductClicked);

	connect(
		&m_products_page,
		&ProductsSubPage::GoToCreateProduct,
		this,
		&ProductPagesController::OnGoToCreateProduct);
}

void ProductPagesController::ConnectViewPage()
{
	connect(
		&m_view_page,
		&ProductViewSubPage::GoBack,
		this,
		&ProductPagesController::GoBack);

//	void EditProduct();
	//	void DeleteProduct();
}

void ProductPagesController::ConnectCreatePage()
{
	connect(
		&m_create_page,
		&ProductCreateSubPage::GoBack,
		this,
		&ProductPagesController::GoBack);

	connect(
		&m_create_page,
		&ProductCreateSubPage::CreateProduct,
		this,
		&ProductPagesController::OnCreateProduct);
}

void ProductPagesController::OnProductClicked(const Product& product)
{
	PageData data{};
	data.setValue(product);
	emit ChangeSubPage(MainSubPages::VIEW_PRODUCT, data);
}

void ProductPagesController::OnGoToCreateProduct(IdType list_id)
{
	m_list_id = list_id;
	m_create_page.Clear();
	emit ChangeSubPage(MainSubPages::CREATE_PRODUCT);
}

void ProductPagesController::OnCreateProduct()
{
	AddProductModel model{m_hostname};

	ProductCategory category;
	category.id = 1;
	category.name = "";

	Product new_product;
	new_product.id = 0;
	new_product.name = m_create_page.GetName();
	new_product.price = m_create_page.GetPrice();
	new_product.amount = m_create_page.GetAmount();
	new_product.priority = m_create_page.GetPriority();
	new_product.is_bought = m_create_page.GetIsBought();
	new_product.category = category;
	new_product.buy_until_date = m_create_page.GetBuyUntil();
	QDateTime date = QDateTime::currentDateTime();
	new_product.add_date = date.toString("yyyy-MM-dd hh:mm:ss");
	new_product.purchase_date = "";
	new_product.list_id = m_list_id;

	auto request  = model.FormRequest(new_product);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Message(
			QString("Error!"),
			QString::fromStdString(response.reason));
		return ;
	}

	auto product_id = model.ParseResponse(response);

	emit GoBack();
}

bool ProductPagesController::UpdateProductsPage()
{
	GetProductsModel model{m_hostname};
	List list = m_products_page.get_list();
	auto request  = model.FormRequest(list.id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Message(
			QString("Error occured"),
			QString::fromStdString(response.reason));
		return false;
	}

	auto products = model.ParseResponse(response);

	m_products_page.Update(products);
	return true;
}

bool ProductPagesController::UpdateProductsPage(List list)
{
	GetProductsModel model{m_hostname};
	m_products_page.set_list(list);
	auto request  = model.FormRequest(list.id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Message(
			QString("Error occured"),
			QString::fromStdString(response.reason));
		return false;
	}

	auto products = model.ParseResponse(response);

	m_products_page.Update(products);
	return true;
}

bool ProductPagesController::UpdateViewPage(Product product)
{
	m_view_page.set_product(product);
	m_view_page.Update();
	return true;
}
