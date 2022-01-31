#include "AddIncomeHandler.h"

#include "../Common.h"
#include "Net/Parsing.h"

#include "Server/Error.h"
#include "Server/Utils.h"
#include "Utils/IncomeUtils.h"

#include "../libdal/Exceptions/SQLFailure.h"

AddIncomeHandler::AddIncomeHandler(IDbFacade::Ptr facade)
  : AuthorizedHandler(std::move(facade))
{
}

Net::Response AddIncomeHandler::AuthHandle(const Net::Request& request)
{
	if(request.method == Net::HTTP_METHOD_POST)
	{
		auto dto = m_parser.Parse(request.json_payload);
		dto.user_id = request.uid;

		IncomeId out_dto;

		try
		{
			out_dto.id = m_facade->AddIncome(dto).value();
		}
		catch (const SQLFailure& e)
		{
			throw FormErrorResponse(
				NetError::Status::HTTP_CONFLICT,
				"Unable to create resource");
		}

		return FormJSONResponse(m_formatter.Format(out_dto));
	}

	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
