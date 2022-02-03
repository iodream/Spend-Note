#include <QJsonArray>

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
	Q_UNUSED(request);
	auto income_id = std::get<long long>(m_params.Get(Params::INCOME_ID));

	if (m_facade->RemoveIncome(income_id)) {
		return FormEmptyResponse();
	}
	else {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}
}
