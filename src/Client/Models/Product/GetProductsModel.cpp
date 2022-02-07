#include "GetProductsModel.h"

Net::Request GetProductsModel::FormRequest(IdType list_id)
{
	Net::Request request;
	request.uri = m_hostname + "/lists/" + std::to_string(list_id) + "/products";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<Product> GetProductsModel::ParseResponse(const Net::Response response)
{
	std::vector<Product> products;

	products = m_parser.Parse(response.json_payload.array());

	return products;
}
