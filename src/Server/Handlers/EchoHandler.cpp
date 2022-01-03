#include <QJsonObject>

#include "EchoHandler.h"
#include "../ClientError.h"

EchoHandler::InDTO EchoHandler::Parser::Parse(const QJsonDocument& json_doc)
{
    InDTO dto;
    auto json = json_doc.object();
	if (json.contains("msg") && json["msg"].isString()) {
		dto.msg = json["msg"].toString().toStdString();
	}
	else {
		throw BadRequestError{"Failed to parse \"msg\" field"};
	}
	return dto;
}

QJsonDocument EchoHandler::Formatter::Format(const OutDTO& dto)
{
	QJsonObject json;
	json["msg"] = dto.msg.c_str();
	return QJsonDocument{json};
}

QJsonDocument EchoHandler::Handle(const QJsonDocument& json_doc)
{
    auto in_dto = m_parser.Parse(json_doc);
    OutDTO out_dto{in_dto.msg};
    return m_formatter.Format(out_dto);
}
