#include "GetListsModel.h"

Net::Request GetListsModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/lists";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<List> GetListsModel::ParseResponse(const Net::Response& response)
{
	std::vector<List> lists;

	lists = m_parser.Parse(response.json_payload.array());

	return lists;
}
