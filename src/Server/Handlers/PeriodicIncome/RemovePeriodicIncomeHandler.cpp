#include <QJsonArray>

#include "RemovePeriodicIncomeHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

RemovePeriodicIncomeHandler::RemovePeriodicIncomeHandler()
{
}

Net::Response RemovePeriodicIncomeHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto income_id = std::get<long long>(m_params.Get(Params::PERIODIC_INCOME_ID));

	if (!m_facade->GetPeriodicIncomeById(income_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}

	if (!m_facade->CanUserEditPeriodicIncome(request.uid, income_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Remove periodic income with id \"" + std::to_string(income_id) + "\" is forbidden");
	}

	m_facade->RemovePeriodicIncome(income_id);
	return FormEmptyResponse();
}
