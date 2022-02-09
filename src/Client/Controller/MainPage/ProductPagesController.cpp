#include "ProductPagesController.h"

#include "Models/Product/GetProductsModel.h"

#include "Net/Constants.h"

ProductPagesController::ProductPagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	ProductsSubPage& list_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_list_page{list_page}
{
	ConnectListPage();
}

void ProductPagesController::ConnectListPage()
{




}

bool ProductPagesController::UpdateListPage()
{
	GetProductsModel model{m_hostname};
	List list = m_list_page.get_list();
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

	m_list_page.Update(products);
	return true;
}

bool ProductPagesController::UpdateListPage(List list)
{
	GetProductsModel model{m_hostname};
	m_list_page.set_list(list);
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

	m_list_page.Update(products);
	return true;
}


