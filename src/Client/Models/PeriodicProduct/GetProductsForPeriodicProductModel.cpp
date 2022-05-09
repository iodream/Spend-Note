#include "GetProductsForPeriodicProductModel.h"

Net::Request GetProductsForPeriodicProductModel::FormRequest(IdType list_id, IdType periodic_product_id)
{
	Net::Request request;
	request.uri = m_hostname + "/lists/" + std::to_string(list_id) + "/periodic-products/" + std::to_string(periodic_product_id) + "/products";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<Product> GetProductsForPeriodicProductModel::ParseResponse(const Net::Response response)
{
	std::vector<Product> products;

	products = m_parser.Parse(response.json_payload.array());

	return products;
}
