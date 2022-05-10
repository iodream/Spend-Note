#include "RemovePeriodicProductModel.h"

Net::Request RemovePeriodicProductModel::FormRequest(const PeriodicProductId& product_id)
{
	Net::Request request;
	request.uri = m_hostname + "/periodic-products/" + std::to_string(product_id.id);
	request.method = Net::HTTP_METHOD_DELETE;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}
