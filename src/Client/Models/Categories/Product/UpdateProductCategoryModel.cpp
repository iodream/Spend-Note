#include "UpdateProductCategoryModel.h"


Net::Request UpdateProductCategoryModel::FormRequest(const ProductCategory& product_category)
{
	Net::Request request;
	request.uri = m_hostname + "/product-categories/" + std::to_string(product_category.id);
	request.method = Net::HTTP_METHOD_PUT;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(product_category));
	return request;
}
