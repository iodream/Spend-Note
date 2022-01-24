#include <QJsonArray>

#include "AddProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

AddProductHandler::AddProductHandler(IDbFacade::Ptr facade)
	: AuthorizedHandler(std::move(facade))
{
}

AddProductHandler::JSONParser::DTO AddProductHandler::JSONParser::Parse(
	const QJsonDocument& payload)
{
	auto json = payload.object();
	return ParseProduct(json);
}

QJsonDocument AddProductHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;

	json["id"] = std::to_string(dto.id).c_str();

	return QJsonDocument{json};
}

Net::Response AddProductHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_POST) {
		auto in_dto = m_parser.Parse(request.json_payload);

		JSONFormatter::DTO out_dto;

		try {
			out_dto.id = m_facade->AddProduct(in_dto).value();
		}
		catch (const SQLFailure& ex) {
			return FormErrorResponse(
				NetError::Status::HTTP_CONFLICT,
				"Unable to create resource");
		}

		return FormJSONResponse(
			m_formatter.Format(out_dto),
			Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CREATED);
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
