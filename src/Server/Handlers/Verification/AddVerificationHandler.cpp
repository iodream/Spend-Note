#include "AddVerificationHandler.h"

#include <memory>
#include <QJsonObject>
#include <QDateTime>
#include <QString>

#include "../Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Net/Parsing.h"
#include "Logger/ScopedLogger.h"

const unsigned long code_expiration_in_secs = 900;

AddVerificationHandler::JSONParser::Verification AddVerificationHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	SCOPED_LOGGER;
	Verification dto;
	auto json = payload.object();

	try {
		SafeReadString(json, "email", dto.email);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response AddVerificationHandler::Handle(Net::Request& request)
{
	SCOPED_LOGGER;

	auto dto = m_parser.Parse(request.json_payload);
	std::optional<db::User> user;
	try {
		user = m_facade->GetUserByEmail(dto.email);
	}
	catch (const db::DatabaseFailure& e) {
		return FormErrorResponse(
			InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
			"User was not gotten because database error occurred");
		}

	if (!user.has_value()) {
		return FormErrorResponse(
			InternalError::Status::HTTP_NOT_FOUND,
			"Such user not found");
	}

	std::optional<db::VerificationCode> verification;
	try {
		verification = m_facade->GetVerificationCodeByUserId(user.value().id);
	}
	catch (const db::DatabaseFailure& e) {
		return FormErrorResponse(
			NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
			"Such verification code was not gotten because database error occurred");
	}

	if (verification.has_value()) {
		try {
			m_facade->RemoveVerificationCode(verification.value().id);
		}
		catch (const db::DatabaseFailure& e) {
			return FormErrorResponse(
				NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
				"Such verification code was not removed because database error occurred");
		}
	}

	const std::string code = m_code_formatter.FormatVerificationCode(code_length);

	try
	{
		QDateTime expiration_time(QDateTime::currentDateTime().addSecs(code_expiration_in_secs));
		m_facade->AddVerificationCode(db::VerificationCode {0, user.value().id, code,
			expiration_time.toString(Qt::ISODate).toStdString()});
	}
	catch(const db::DatabaseFailure& e)
	{
		return FormErrorResponse(
			InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
			"Verification code not created because database error occurred");
	}

	try
	{
		//m_sender.SendEmail(dto.email, code);
		return FormEmptyResponse(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	}
	catch (Poco::Exception& exc)
	{
		return FormErrorResponse(
			Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_BAD_REQUEST,
			"Impossible to send email");
	}
}
