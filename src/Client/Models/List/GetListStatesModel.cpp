#include "GetListStatesModel.h"

Net::Request GetListStatesModel::FormRequest()
{
	Net::Request request;
	request.uri = m_hostname + "/lists/states";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<ListState> GetListStatesModel::ParseResponse(const Net::Response& response)
{
	std::vector<ListState> list_states;

	list_states = m_parser.Parse(response.json_payload.array());

	return list_states;
}
