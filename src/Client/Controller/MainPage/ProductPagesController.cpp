#include "ProductPagesController.h"

#include "Models/Product/GetProductsModel.h"
#include "Models/Product/RemoveProductModel.h"

#include "Net/Constants.h"

ProductPagesController::ProductPagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	ProductsSubPage& products_page,
	ProductViewSubPage& view_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_products_page{products_page}
	, m_view_page{view_page}
{
	ConnectProductsPage();
	ConnectViewPage();
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
}

void ProductPagesController::ConnectViewPage()
{
	connect(
		&m_view_page,
		&ProductViewSubPage::GoBack,
		this,
		&ProductPagesController::GoBack);

	connect(
		&m_view_page,
		&ProductViewSubPage::DeleteProduct,
		this,
		&ProductPagesController::OnDeleteProduct);
}

void ProductPagesController::OnProductClicked(const Product& product)
{
	PageData data{};
	data.setValue(product);
	emit ChangeSubPage(MainSubPages::VIEW_PRODUCT, data);
}

void ProductPagesController::OnDeleteProduct()
{
	RemoveProductModel model{m_hostname};
	ProductId id{m_view_page.get_product().id};
	auto request = model.FormRequest(id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Message(
			QString("Error occured"),
			QString::fromStdString(response.reason));
		return;
	}

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
