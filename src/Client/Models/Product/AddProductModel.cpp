#include "AddProductModel.h"

#include "Net/Parsing.h"

Net::Request AddProductModel::FormRequest(const Product& product)
{
	Net::Request request;
	request.uri = m_hostname + "/lists/" + std::to_string(product.list_id) + "/products";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(product));
	return request;
}

ProductId AddProductModel::ParseResponse(const Net::Response& response)
{
	ProductId product_id;

	product_id = m_parser.Parse(response.json_payload.object());

	return product_id;
}
