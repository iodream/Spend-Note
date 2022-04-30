#include "CheckVerificationHandler.h"

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

CheckVerificationHandler::JSONParser::Verification CheckVerificationHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	SCOPED_LOGGER;
	Verification dto;
	auto json = payload.object();

	try {
		SafeReadString(json, "email", dto.email);
		SafeReadString(json, "code", dto.code);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response CheckVerificationHandler::Handle(Net::Request& request)
{
	SCOPED_LOGGER;

	auto dto = m_parser.Parse(request.json_payload);

	std::optional<db::User> user;
	try {
		user = m_facade->GetUserByEmail(dto.email);
	}
	catch (const db::DatabaseFailure& e) {
		return FormErrorResponse(
			NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
			"Such user was not get because database error occurred");
	}

	if (!user.has_value()) {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"User not found");
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

	if (!verification.has_value()) {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Verification code not found");
	}

	QDateTime current_time(QDateTime::currentDateTime());

	if (current_time > QDateTime::fromString(QString::fromStdString(verification.value().expiration_time), Qt::ISODate)) {
		try {
			m_facade->RemoveVerificationCode(verification.value().id);
		}
		catch (const db::DatabaseFailure& e) {
			return FormErrorResponse(
				NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
				"Such verification code was not removed because database error occurred");
		}
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Verification code not found");
	}
	else {
		if (dto.code == verification.value().code) {
			try {
				m_facade->UpdateUserVerification(user.value().id);
			}
			catch (const db::DatabaseFailure& e) {
				return FormErrorResponse(
					NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
					"Such user was not updated because database error occurred");
			}
			try {
				m_facade->RemoveVerificationCode(verification.value().id);
			}
			catch (const db::DatabaseFailure& e) {
				return FormErrorResponse(
					NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
					"Such verification code was not removed because database error occurred");
			}
			return FormEmptyResponse(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
		}
	}

	return FormErrorResponse(
		NetError::Status::HTTP_UNAUTHORIZED,
		"Wrong verification code");
}
