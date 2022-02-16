#include "GetProductCategoriesModel.h"

Net::Request GetProductCategoriesModel::FormRequest()
{
	Net::Request request;
	request.uri = m_hostname + "/products/categories";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<ProductCategory> GetProductCategoriesModel::ParseResponse(const Net::Response& response)
{
	std::vector<ProductCategory> product_categories;

	product_categories = m_parser.Parse(response.json_payload.array());

	return product_categories;
}
