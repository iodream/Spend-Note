#include "RemoveListModel.h"

Net::Request RemoveListModel::FormRequest(const ListId& list_id)
{
	Net::Request request;
	request.uri = m_hostname + "/lists/" + std::to_string(list_id.id);
	request.method = Net::HTTP_METHOD_DELETE;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}
