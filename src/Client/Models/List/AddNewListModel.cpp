#include "AddNewListModel.h"
#include "../../Entities/Parsers.h"

Net::Request  AddNewListsModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/lists";
	request.method = Net::HTTP_METHOD_POST;
	return request;
}

ListId AddNewListsModel::ParseResponse(const Net::Response& response)
{
	ListIdJSONParser id_parser;
	return id_parser.Parse(response.json_payload.object());
}
