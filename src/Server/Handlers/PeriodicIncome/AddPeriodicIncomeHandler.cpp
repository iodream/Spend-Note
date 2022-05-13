#include <QJsonArray>

#include "AddPeriodicIncomeHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

AddPeriodicIncomeHandler::AddPeriodicIncomeHandler()
{
}

Net::Response AddPeriodicIncomeHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));

	if (request.uid != user_id){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't create periodic income for user with id \"" + std::to_string(user_id) + "\"");
	}

	auto json_payload = request.json_payload.object();
	auto income = m_parser.Parse(json_payload);
	auto income_db = ToDBPeriodicIncome(income, user_id);
	PeriodicIncomeId income_id;
	try {
		income_id.id = m_facade->AddPeriodicIncome(income_db).value();
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
