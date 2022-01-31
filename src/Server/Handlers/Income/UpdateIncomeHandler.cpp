#include <QJsonArray>
#include "UpdateIncomeHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils/IncomeUtils.h"
#include "../libdal/Exceptions/SQLFailure.h"

UpdateIncomeHandler::UpdateIncomeHandler(IDbFacade::Ptr facade)
	: AuthorizedHandler(std::move(facade))
{
}

Net::Response UpdateIncomeHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_PUT) {
		auto in_dto = m_parser.Parse(request.json_payload);

		if (m_facade->UpdateIncome(in_dto)) {
			return FormEmptyResponse();
		}
		else {
			return FormErrorResponse(
				NetError::Status::HTTP_NOT_FOUND,
				"Resource not found");
		}
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
