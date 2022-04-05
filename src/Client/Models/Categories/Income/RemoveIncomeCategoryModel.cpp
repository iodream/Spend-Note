#include "RemoveIncomeCategoryModel.h"

Net::Request RemoveIncomeCategoryModel::FormRequest(const IncomeCategoryId& category_id)
{
	Net::Request request;
	request.uri = m_hostname + "/income-categories/" + std::to_string(category_id.id);
	request.method = Net::HTTP_METHOD_DELETE;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}
