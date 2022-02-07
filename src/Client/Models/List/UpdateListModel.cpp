#include "UpdateListModel.h"

Net::Request UpdateListModel::FormRequest(const List& list)
{
	Net::Request request;
	request.uri = m_hostname + "/lists/" + std::to_string(list.id);
	request.method = Net::HTTP_METHOD_PUT;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(list));
	return request;
}
