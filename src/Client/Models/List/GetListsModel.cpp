#include "GetListsModel.h"
#include "Net/Parsing.h"
#include "Utils.h"

Net::Request GetListsModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/lists";
	request.method = Net::HTTP_METHOD_GET;
	return request;
}

void GetListsModel::JSONParser::Parse(QJsonArray json, std::vector<List>& lists)
{
	for (auto it = json.begin(); it != json.end(); it++) {
		lists.push_back(ParseList((*it).toObject()));
	}
}

std::vector<List> GetListsModel::ParseResponse(const Net::Response& response)
{
	std::vector<List> lists;

	m_parser.Parse(response.json_payload.array(), lists);

	return lists;
}
