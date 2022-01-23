#include "SignupHandler.h"

#include <memory>
#include <QJsonObject>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include "Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Net/Parsing.h"

SignupHandler::SignupHandler(IDbFacade::Ptr facade)
	: ICommandHandler(std::move(facade))
{

}

QJsonDocument SignupHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;
	json["id"] = std::to_string(dto.id).c_str();
	return QJsonDocument{json};
}

SignupHandler::JSONParser::DTO SignupHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	DTO dto;
	auto json = payload.object();

	try {
		SafeReadString(json, "login", dto.login);
		SafeReadString(json, "password", dto.passwd_hash);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response SignupHandler::Handle(Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_POST) {
		auto dto = m_parser.Parse(request.json_payload);
		auto user = m_facade->GetUserByLogin(dto.login);

		if (user)
		{
			return FormErrorResponse(
				Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CONFLICT,
				"Login already exists");
		}

		try
		{
			// Replace when libdal merged
			//auto id = m_facade->AddUser(User {0, dto.login, dto.passwd_hash});
			//JSONFormatter::DTO out_dto{id.value()};
			m_facade->AddUser(User {0, dto.login, dto.passwd_hash});
			IdType id = 1;
			JSONFormatter::DTO out_dto{id};
			return FormJSONResponse(m_formatter.Format(out_dto));
		}
		catch(const DatabaseFailure& e)
		{
			return FormErrorResponse(
				InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
				"User not registered");
		}
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
