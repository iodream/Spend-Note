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
	auto income_id = std::get<long long>(m_params.Get(Params::INCOME_ID));
	auto json_payload = request.json_payload.object();
	auto income = m_parser.Parse(json_payload);

	if (income_id != income.id){
		return FormErrorResponse(
			NetError::Status::HTTP_BAD_REQUEST,
			"Income id in uri and in json are not equal");
	}

	if (!m_facade->CanUserEditIncome(request.uid, income_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Update income with id " + std::to_string(income_id) + " is forbidden");
	}

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
