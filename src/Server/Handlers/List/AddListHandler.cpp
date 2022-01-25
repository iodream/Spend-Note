#include "AddListHandler.h"

#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

AddListHandler::AddListHandler(IDbFacade::Ptr facade)
	: AuthorizedHandler(std::move(facade))
{
}

List AddListHandler::JSONParser::Parse(
	const QJsonDocument& payload)
{
	auto json = payload.object();

	List list;
	SafeReadString(json, "name", list.name);
	SafeReadId(json, "state_id", list.state_id);

	return list;
}

QJsonDocument AddListHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;

	json["id"] = std::to_string(dto.id).c_str();

	return QJsonDocument{json};
}

Net::Response AddListHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_POST) {
		auto in_dto = m_parser.Parse(request.json_payload);
		in_dto.owner_id = request.uid;

		try
		{
			JSONFormatter::DTO out_dto;
			out_dto.id = m_facade->AddList(in_dto).value();

			return FormJSONResponse(
				m_formatter.Format(out_dto),
				Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CREATED);
		}
		catch (const SQLFailure& ex)
		{
			return FormErrorResponse(
				NetError::Status::HTTP_CONFLICT,
				"Unable to create resource");
		}
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
