#include "RemoveProductCategoryModel.h"

Net::Request RemoveProductCategoryModel::FormRequest(const ProductCategoryId& product_category_id)
{
	Net::Request request;
	request.uri = m_hostname + "/product-categories/" + std::to_string(product_category_id.id);
	request.method = Net::HTTP_METHOD_DELETE;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}
