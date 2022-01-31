#include <memory>
#include <QJsonObject>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include "LoginHandler.h"
#include "Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Net/Parsing.h"
#include "Logger/ScopedLogger.h"

LoginHandler::LoginHandler(IDbFacade::Ptr facade)
	: ICommandHandler(std::move(facade))
{

}

QJsonDocument LoginHandler::JSONFormatter::Format(const Token& dto)
{
	SCOPED_LOGGER;
	QJsonObject json;
	json["token"] = dto.token.c_str();
	return QJsonDocument{json};
}

LoginHandler::JSONParser::Login LoginHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	SCOPED_LOGGER;
	Login dto;
	auto json = payload.object();

	try {
		SafeReadString(json, "login", dto.login);
		SafeReadString(json, "password", dto.passwd_hash);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response LoginHandler::Handle(Net::Request& request)
{
	SCOPED_LOGGER;
	if (request.method == Net::HTTP_METHOD_POST) {
		auto dto = m_parser.Parse(request.json_payload);
		auto user = m_facade->GetUserByLogin(dto.login);

		if(!user || dto.passwd_hash != user->password) {
			return FormErrorResponse(
			NetError::Status::HTTP_UNAUTHORIZED,
			"Invalid login data");
		}

		Poco::JWT::Token token;
		token.setType("JWT");

		token.payload().set("id", std::to_string(user->id));
		token.payload().set("login", std::string(user->login));

		token.setIssuedAt(Poco::Timestamp());

		Poco::JWT::Signer signer(user->password);
		std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
		JSONFormatter::Token out_dto{jwt};
		return FormJSONResponse(m_formatter.Format(out_dto));
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
