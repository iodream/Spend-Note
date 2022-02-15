#include "GetIncomesModel.h"

Net::Request GetIncomesModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/incomes";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<Income> GetIncomesModel::ParseResponse(const Net::Response response)
{
	std::vector<Income> incomes;

	incomes = m_parser.Parse(response.json_payload.array());

	return incomes;
}
