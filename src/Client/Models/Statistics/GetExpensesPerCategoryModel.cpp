#include "GetExpensesPerCategoryModel.h"

Net::Request GetExpensesPerCategoryModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/expenses-per-category";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<StatisticPerCategory> GetExpensesPerCategoryModel::ParseResponse(const Net::Response& response)
{
	std::vector<StatisticPerCategory> expenses;

	expenses = m_parser.Parse(response.json_payload.array());

	return expenses;
}
