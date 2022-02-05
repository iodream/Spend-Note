#include "GetIncomesModel.h"

Net::Request GetIncomesModel::FormRequest()
{
	Net::Request request;
	request.uri = m_hostname + "users/" + /*user_id*/ "/incomes";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<Income<QString> > GetIncomesModel::ParseResponse(const Net::Response response)
{
	std::vector<Income<QString>> incomes;

	incomes = m_parser.Parse(response.json_payload);

	return incomes;
}
