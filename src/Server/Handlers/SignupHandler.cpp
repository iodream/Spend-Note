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
#include <iostream>

SignupHandler::SignupHandler(IDbFacade::Ptr facade)
	: ICommandHandler(std::move(facade))
{

}

SignupHandler::JSONParser::Credentials SignupHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	Credentials dto;
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
			m_facade->AddUser(User {0, dto.login, dto.passwd_hash}).value();
			return FormEmptyResponse(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
		}
		catch(const DatabaseFailure& e)
		{
			return FormErrorResponse(
				InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
				"User not created because database error occured");
		}
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
