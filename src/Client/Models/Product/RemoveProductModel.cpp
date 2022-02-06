#include "RemoveProductModel.h"

Net::Request RemoveProductModel::FormRequest(const ProductId& product_id)
{
	Net::Request request;
	request.uri = m_hostname + "products/" + std::to_string(product_id.id);
	request.method = Net::HTTP_METHOD_DELETE;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}
