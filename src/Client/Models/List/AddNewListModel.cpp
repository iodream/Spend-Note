#include "AddNewListModel.h"

Net::Request  AddNewListsModel::FormRequest(const List& list, const IdType& user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/lists";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(list));
	return request;
}

ListId AddNewListsModel::ParseResponse(const Net::Response& response)
{
	return m_parser.Parse(response.json_payload.object());
}
