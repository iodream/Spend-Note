#include "GetBalanceModel.h"

Net::Request GetBalanceModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/balance";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

Balance GetBalanceModel::ParseResponse(const Net::Response& response)
{
	Balance balance;

	balance = m_parser.Parse(response.json_payload.object());

	return balance;
}
