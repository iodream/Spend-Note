#include "AddIncomeModel.h"

Net::Request AddIncomeModel::FormRequest(const Income& income)
{
	Net::Request request;
	request.uri = m_hostname +"/users/" + std::to_string(income.id) +  "/incomes" ;
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(income));
	return request;
}

IncomeId AddIncomeModel::ParseResponse(const Net::Response& response)
{
	IncomeId income_id;

	income_id = m_parser.Parse(response.json_payload.object());

	return income_id;
}

