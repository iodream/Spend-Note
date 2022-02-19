#include "GetDailyListModel.h"

Net::Request GetDailyListModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/daily-list";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<Product> GetDailyListModel::ParseResponse(const Net::Response response)
{
	std::vector<Product> products;

	products = m_parser.Parse(response.json_payload.array());

	return products;
}
