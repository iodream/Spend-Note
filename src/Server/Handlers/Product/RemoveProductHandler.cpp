#include <QJsonArray>

#include "RemoveProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

RemoveProductHandler::RemoveProductHandler(IDbFacade::Ptr facade)
	: AuthorizedHandler(std::move(facade))
{
}

RemoveProductHandler::JSONParser::DTO RemoveProductHandler::JSONParser::Parse(
	const QJsonDocument& payload)
{
	DTO dto;
	auto json = payload.object();
	SafeReadId(json, "id", dto.id);
	return dto;
}

Net::Response RemoveProductHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_DELETE) {
		auto in_dto = m_parser.Parse(request.json_payload);

		if (m_facade->RemoveProduct(in_dto.id)) {
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