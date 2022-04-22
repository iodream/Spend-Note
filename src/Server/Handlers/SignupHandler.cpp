#include "SignupHandler.h"

#include <memory>
#include <QJsonObject>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include "Poco/DigestStream.h"
#include "Poco/MD5Engine.h"

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
		SafeReadString(json, "password", dto.passwd_hash);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

std::string SignupHandler::CreateSalt()
{
	std::string salt;

	std::random_device random_device; // create object for seeding
	std::mt19937 engine{random_device()}; // create engine and seed it
	std::uniform_int_distribution<> dist(33,126); // create distribution for integers with [1; 9] range

	for(int i = 0; i < Net::SALT_SIZE; ++i)
	{
		auto random_number = dist(engine);
		salt += char(random_number);
	}
	std::shuffle(salt.begin(), salt.end(), engine);

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
		Poco::MD5Engine md5;
		Poco::DigestOutputStream ostr(md5);
		dto.salt = CreateSalt();
		ostr << dto.passwd_hash + dto.salt;
		ostr.flush();

		const Poco::DigestEngine::Digest& digest = md5.digest();
		dto.passwd_hash= Poco::DigestEngine::digestToHex(digest);

		m_facade->AddUser(db::User {0, dto.login, dto.passwd_hash, dto.salt}).value();
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
