#include <QJsonObject>

#include "EchoHandler.h"
#include "Common.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "Logger/ScopedLogger.h"

EchoHandler::JSONParser::Message EchoHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	SCOPED_LOGGER;
	Message dto;
	auto json = payload.object();

	try {
		SafeReadString(json, "msg", dto.msg);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

QJsonDocument EchoHandler::JSONFormatter::Format(
		const EchoHandler::JSONFormatter::Message& dto)
{
	SCOPED_LOGGER;
	QJsonObject json;
	json["msg"] = dto.msg.c_str();
	return QJsonDocument{json};
}

Net::Response EchoHandler::Handle(Net::Request& request)
{
	SCOPED_LOGGER;
	if (request.method == Net::HTTP_METHOD_POST) {
		Net::Response response;
		auto in_dto = m_parser.Parse(request.json_payload);
		JSONFormatter::Message out_dto{in_dto.msg};
		return FormJSONResponse(m_formatter.Format(out_dto));
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
