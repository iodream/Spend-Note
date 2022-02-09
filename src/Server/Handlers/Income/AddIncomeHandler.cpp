#include "AddIncomeHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

AddIncomeHandler::AddIncomeHandler()
{
}

Net::Response AddIncomeHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto json_payload = request.json_payload.object();
	auto income = m_parser.Parse(json_payload);
	auto income_db = ToDBIncome(income);
	IncomeId income_id;
	try {
		income_id.id = m_facade->AddIncome(income_db).value();
	}
	catch (const db::SQLFailure& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_CONFLICT,
			"Unable to create resource");
	}
	return FormJSONResponse(
		m_formatter.Format(income_id),
		Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CREATED);
}

