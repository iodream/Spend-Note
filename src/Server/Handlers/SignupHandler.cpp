#include "SignupHandler.h"

#include <memory>
#include <QJsonObject>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include <Poco/Exception.h>
#include <QDateTime>

#include "Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Net/Parsing.h"
#include <iostream>
#include "Logger/ScopedLogger.h"

const QString DATE_FORMAT_YYYY_MM_DD_HH_MM_SS = "yyyy-MM-dd hh:mm:ss";
const unsigned long code_expiration_in_secs = 900;

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
		SafeReadString(json, "email", dto.email);
		SafeReadString(json, "password", dto.passwd_hash);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response SignupHandler::Handle(Net::Request& request)
{
	SCOPED_LOGGER;

	auto dto = m_parser.Parse(request.json_payload);
	auto user = m_facade->GetUserByEmail(dto.email);

	if (user)
	{
		return FormErrorResponse(
			Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CONFLICT,
			"User with this email already exists");
	}

	const std::string code = m_code_formatter.FormatVerificationCode(code_length);

	try
	{
		m_sender.SendEmail(dto.email, code);
	}
	catch (Poco::Exception& exc)
	{
		return FormErrorResponse(
			Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_BAD_REQUEST,
			"Impossible to send email");
	}

	try
	{
		auto user_id = m_facade->AddUser(db::User {0, dto.email, dto.passwd_hash, false}).value();

		QDateTime expiration_time(QDateTime::currentDateTime().addSecs(code_expiration_in_secs));
		m_facade->AddVerificationCode(db::VerificationCode {0, user_id, code,
			expiration_time.toString(DATE_FORMAT_YYYY_MM_DD_HH_MM_SS).toStdString()});

		qInfo() << "Registered new user: " << QString::fromStdString(dto.email) << "\n";
		return FormEmptyResponse(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	}
	catch(const db::DatabaseFailure& e)
	{
		return FormErrorResponse(
			InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
			"User not created because database error occured");
	}

}
