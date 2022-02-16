#include "RemoveIncomeHandler.h"

#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"
#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

RemoveIncomeHandler::RemoveIncomeHandler()
{
}

Net::Response RemoveIncomeHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto income_id = std::get<long long>(m_params.Get(Params::INCOME_ID));

	if (!m_facade->CanUserEditIncome(request.uid, income_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Remove income with id " + std::to_string(income_id) + " is forbidden");
	}

	if (m_facade->RemoveIncome(income_id)) {
		return FormEmptyResponse();
	}
	else {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}
}
