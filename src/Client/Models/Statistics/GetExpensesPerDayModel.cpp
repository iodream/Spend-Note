#include "GetExpensesPerDayModel.h"

Net::Request GetExpensesPerDayModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/expenses-per-day";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<ExpensePerDay> GetExpensesPerDayModel::ParseResponse(const Net::Response& response)
{
	std::vector<ExpensePerDay> expenses;

	expenses = m_parser.Parse(response.json_payload.array());

	return expenses;
}
