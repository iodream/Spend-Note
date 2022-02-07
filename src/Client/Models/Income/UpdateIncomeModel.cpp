#include "UpdateIncomeModel.h"

Net::Request GetIncomesModel::FormRequest(const Income& income)
{
	Net::Request request;
	request.uri = m_hostname + "incomes/" + std::to_string(income.id);
	request.method = Net::HTTP_METHOD_PUT;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(income));
	return request;
}
