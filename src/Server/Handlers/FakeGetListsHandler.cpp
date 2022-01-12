#include "QJsonObject"

#include "FakeGetListsHandler.h"
#include "Common.h"
#include "Net/Parsing.h"

#include "Server/Error.h"
#include "Server/Utils.h"

FakeGetListsHandler::JSONParser::DTO FakeGetListsHandler::JSONParser::Parse(
	const QJsonDocument& token_body)
{
	FakeGetListsHandler::JSONParser::DTO dto;
	auto json = token_body.object();

	try {
		SafeReadString(json, "user", dto.user);
	}  catch (const ParsingError& ex) {
		throw Net::BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

QJsonDocument FakeGetListsHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;
	json["msg"] = std::string{dto.msg}.append(dto.user).c_str();
	return QJsonDocument{json};
}

Net::Response FakeGetListsHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_GET) {
		auto in_dto = m_parser.Parse(request.jwt_token_body);
		JSONFormatter::DTO out_dto{
			in_dto.user,
			"Some lists msg for user "
		};
		return FormJSONResponse(m_formatter.Format(out_dto));
	}
	return FormErrorResponse(
		Net::NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
