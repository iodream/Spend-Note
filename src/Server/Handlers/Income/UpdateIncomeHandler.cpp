#include "UpdateIncomeHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

UpdateIncomeHandler::UpdateIncomeHandler()
{
}

Net::Response UpdateIncomeHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto json_payload = request.json_payload.object();
	auto income = m_parser.Parse(json_payload);
	auto income_db = ToDBIncome(income);

	if (m_facade->UpdateIncome(income_db)) {
		return FormEmptyResponse();
	}
	else {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}
}
