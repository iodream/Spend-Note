#include "RemoveIncomeModel.h"

Net::Request RemoveIncomeModel::FormRequest(const IncomeId& income_id)
{
	Net::Request request;
	request.uri = m_hostname + "incomes/" + std::to_string(income_id.id);
	request.method = Net::HTTP_METHOD_DELETE;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}
