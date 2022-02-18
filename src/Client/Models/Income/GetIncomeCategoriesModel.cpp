#include "GetIncomeCategoriesModel.h"

Net::Request GetIncomeCategoriesModel::FormRequest()
{
	Net::Request request;
	request.uri = m_hostname + "/incomes/categories";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<IncomeCategory> GetIncomeCategoriesModel::ParseResponse(const Net::Response& response)
{
	std::vector<IncomeCategory> income_categories;

	income_categories = m_parser.Parse(response.json_payload.array());

	return income_categories;
}
