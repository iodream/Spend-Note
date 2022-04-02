#include "AddIncomeCategoryModel.h"

Net::Request AddIncomeCategoryModel::FormRequest(
	const IdType& user_id,
	const IncomeCategory& income_category)
{
	Net::Request request;
	request.uid = user_id;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/income-categories";
	request.auth_scheme = Net::AUTH_SCHEME_TYPE_BEARER;
	request.json_payload = QJsonDocument(m_formatter.Format(income_category));
	request.method = Net::HTTP_METHOD_POST;
	return request;
}

IncomeCategoryId AddIncomeCategoryModel::ParseResponse(const Net::Response& response)
{
	IncomeCategoryId category_id;
	category_id = m_parser.Parse(response.json_payload.object());
	return category_id;
}
