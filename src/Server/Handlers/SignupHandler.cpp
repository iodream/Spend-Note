#include "SignupHandler.h"

#include <memory>
#include <QJsonObject>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include "Poco/DigestStream.h"
#include "Poco/SHA1Engine.h"

#include <random>
#include <algorithm>

#include "Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Net/Parsing.h"
#include <iostream>
#include "Logger/ScopedLogger.h"
#include "Net/Constants.h"
#include "../Utils.h"

SignupHandler::SignupHandler()
{

}

SignupHandler::JSONParser::Credentials SignupHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	SCOPED_LOGGER;
	Credentials dto;
	auto json = payload.object();

	try {
		SafeReadString(json, "login", dto.login);
		SafeReadString(json, "password", dto.password);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

std::string SignupHandler::CreateSalt()
{
	std::string salt;

	std::sample(Net::SALT_CHARACTERS.begin(), Net::SALT_CHARACTERS.end(), std::back_inserter(salt),
						Net::SALT_SIZE, std::mt19937{std::random_device{}()});

	return salt;
}

Net::Response SignupHandler::Handle(Net::Request& request)
{
	SCOPED_LOGGER;
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
		dto.salt = CreateSalt();
		dto.password_hash = HashingPassword(dto.password, dto.salt);
		m_facade->AddUser(db::User {0, dto.login, dto.password_hash, dto.salt}).value();
		qInfo() << "Registered new user: " << QString::fromStdString(dto.login) << "\n";
		return FormEmptyResponse(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	}
	catch(const db::DatabaseFailure& e)
	{
		return FormErrorResponse(
			InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
			"User not created because database error occured");
	}
}
