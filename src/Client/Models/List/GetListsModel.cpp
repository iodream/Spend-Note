#include "GetListsModel.h"
#include "Net/Parsing.h"
#include "Utils.h"
#include "../Logger/ScopedLogger.h"
Net::Request GetListsModel::FormRequest()
{
	SCOPED_LOGGER;
	Net::Request request;
	request.uri = m_hostname + "list/get_lists";
	request.method = Net::HTTP_METHOD_GET;
	return request;
}

void GetListsModel::JSONParser::Parse(QJsonObject json, std::vector<List>& lists)
{
	SCOPED_LOGGER;
	QJsonArray array;
	SafeReadArray(json, "lists", array);

	for (auto it = array.begin(); it != array.end(); it++) {
		lists.push_back(ParseList((*it).toObject()));
	}
}

std::vector<List> GetListsModel::ParseResponse(const Net::Response& response)
{
	SCOPED_LOGGER;
	std::vector<List> lists;

	m_parser.Parse(response.json_payload.object(), lists);

	return lists;
}
