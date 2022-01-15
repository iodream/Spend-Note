#include <QJsonObject>

#include "Poco/JWT/Token.h"
#include "Poco/JWT/Signer.h"

#include "FakeLoginHandler.h"
#include "../ClientError.h"

FakeLoginHandler::InDTO FakeLoginHandler::Parser::Parse(const QJsonDocument& json_doc)
{
	InDTO dto;
	Q_UNUSED(json_doc);
	return dto;
}

QJsonDocument FakeLoginHandler::Formatter::Format(const OutDTO& dto)
{
	QJsonObject json;
	json["token"] = dto.token.c_str();
	return QJsonDocument{json};
}

QJsonDocument FakeLoginHandler::Handle(const QJsonDocument& json_doc)
{
	Q_UNUSED(json_doc)
	Poco::JWT::Token token;
	token.setType("JWT");
	token.payload().set("name", std::string("Admin"));
	token.setIssuedAt(Poco::Timestamp());

	Poco::JWT::Signer signer("0123456789ABCDEF0123456789ABCDEF");
	std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);

	OutDTO out_dto{jwt};
	return m_formatter.Format(out_dto);
}
