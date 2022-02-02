#include "UpdateIncomeHandler.h"

#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils/IncomeUtils.h"
#include "../libdal/Exceptions/SQLFailure.h"

UpdateIncomeHandler::UpdateIncomeHandler()
{
}

Net::Response UpdateIncomeHandler::AuthHandle(const Net::Request& request)
{
	auto income = m_parser.Parse(request.json_payload);
	auto income_id = std::get<long long>(m_params.Get(Params::INCOME_ID));
	income.id = income_id;

	if (m_facade->UpdateIncome(income)) {
		return FormEmptyResponse();
	}
	else {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}
}
