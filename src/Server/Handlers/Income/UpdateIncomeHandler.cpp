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

Income UpdateIncomeHandler::JSONParser::Parse(
	const QJsonDocument& payload)
{
	SCOPED_LOGGER;
	auto json = payload.object();
	return ParseIncome(json);
}

Net::Response UpdateIncomeHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
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
