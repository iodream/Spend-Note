#include "AddIncomeHandler.h"

#include "../Common.h"
#include "Net/Parsing.h"

#include "Server/Error.h"
#include "Server/Utils.h"
#include "Utils/IncomeUtils.h"

#include "../libdal/Exceptions/SQLFailure.h"

AddIncomeHandler::AddIncomeHandler()
{
}

Net::Response AddIncomeHandler::AuthHandle(const Net::Request& request)
{
	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));

	auto dto = m_parser.Parse(request.json_payload);
	dto.user_id = user_id;

	AddIncomeHandler::JSONFormatter::DTO out_dto;

	try
	{
		out_dto.income_id = m_facade->AddIncome(dto).value();
	}
	catch (const SQLFailure& e)
	{
		throw FormErrorResponse(
			NetError::Status::HTTP_CONFLICT,
			"Unable to create resource");
	}

	return FormJSONResponse(m_formatter.Format(out_dto));
}
