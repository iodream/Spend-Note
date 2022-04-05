#include "UpdateIncomeCategoryModel.h"

Net::Request UpdateIncomeCategoryModel::FormRequest(const IncomeCategory& category)
{
	Net::Request request;
	request.uri = m_hostname + "/income-categories/" + std::to_string(category.id);
	request.method = Net::HTTP_METHOD_PUT;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(category));
	return request;
}
