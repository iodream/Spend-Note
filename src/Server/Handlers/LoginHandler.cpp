#include <memory>

#include <QJsonObject>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include "Poco/DigestStream.h"
#include "Poco/MD5Engine.h"

#include "LoginHandler.h"

#include "Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Net/Parsing.h"
#include "Logger/ScopedLogger.h"

#include "../Utils.h"

LoginHandler::LoginHandler()
{

}

QJsonDocument LoginHandler::JSONFormatter::Format(const OutDto& dto)
{
	SCOPED_LOGGER;
	QJsonObject json;
	json["token"] = dto.token.c_str();
	json["id"] = dto.id;
	return QJsonDocument{json};
}

LoginHandler::JSONParser::Login LoginHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	SCOPED_LOGGER;
	Login dto;
	auto json = payload.object();

	try {
		SafeReadString(json, "email", dto.email);
		SafeReadString(json, "password", dto.password);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response LoginHandler::Handle(Net::Request& request)
{
	SCOPED_LOGGER;


	auto dto = m_parser.Parse(request.json_payload);
	auto user = m_facade->GetUserByEmail(dto.email);

	dto.password_hash = HashingPassword(dto.password, user->salt);
	if(!user || dto.password_hash != user->password_hash || !user.value().verified) {

		return FormErrorResponse(
		NetError::Status::HTTP_UNAUTHORIZED,
		"Invalid login data");
	}

	Poco::JWT::Token token;
	token.setType("JWT");

	token.payload().set("id", FormatId(user->id));
	token.payload().set("email", std::string(user->email));

	token.setIssuedAt(Poco::Timestamp());

	Poco::JWT::Signer signer(user->password_hash);
	std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
	JSONFormatter::OutDto out_dto{jwt, user->id};
	return FormJSONResponse(m_formatter.Format(out_dto));

}
