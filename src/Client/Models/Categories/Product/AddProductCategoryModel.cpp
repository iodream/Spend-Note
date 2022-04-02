#include "AddProductCategoryModel.h"

#include "Net/Parsing.h"
#include "Utils.h"
Net::Request AddProductCategoryModel::FormRequest(const IdType& user_id, const ProductCategory& product_category)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/product-categories";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(product_category));
	return request;
}

ProductCategoryId AddProductCategoryModel::ParseResponse(const Net::Response& response)
{
	ProductCategoryId product_category_id;

	product_category_id = m_parser.Parse(response.json_payload.object());

	return product_category_id;
}

bool AddProductCategoryModel::CheckFields(ProductCategory& product_category)
{
	std::string str = EraseWhitespace(product_category.name.toStdString());
	if(str.empty())
		return false;
	return true;
}
