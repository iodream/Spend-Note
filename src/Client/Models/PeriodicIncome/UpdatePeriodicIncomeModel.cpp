#include "UpdatePeriodicIncomeModel.h"
#include "Utils.h"

Net::Request UpdatePeriodicIncomeModel::FormRequest(const PeriodicIncome& income)
{
	Net::Request request;
	request.uri = m_hostname + "/periodic-incomes/" + std::to_string(income.id);
	request.method = Net::HTTP_METHOD_PUT;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = QJsonDocument(m_formatter.Format(income));
	return request;
}

bool UpdatePeriodicIncomeModel::CheckFields(const PeriodicIncome& income)
{
	std::string str = EraseWhitespace(income.name.toStdString());
	if(str.empty())
		return false;
	str = income.amount;
	if(str.empty())
		return false;
	str = EraseWhitespace(income.category.name.toStdString());
	if(str.empty())
		return false;
	return true;
}
