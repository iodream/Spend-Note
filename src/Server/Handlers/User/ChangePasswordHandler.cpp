#include "ChangePasswordHandler.h"

Net::Response ChangePasswordHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	std::optional<db::VerificationCode> verification;
	try
	{
		verification = m_facade->GetVerificationCodeByUserId(request.uid);
	}
	catch (const db::DatabaseFailure& e)
	{
		return FormErrorResponse(
			NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
			"Such verification code was not gotten because database error occurred");
	}

	if (!verification.has_value())
	{
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Verification code not found");
	}

	QDateTime current_time(QDateTime::currentDateTime());
	auto dto = m_parser.Parse(request.json_payload.object());
	std::string salt = CreateSalt();
	std::string password_hash = HashingPassword(dto.password, salt);

	if (current_time > QDateTime::fromString(QString::fromStdString(verification.value().expiration_time), Qt::ISODate))
	{
		try
		{
			m_facade->RemoveVerificationCode(verification.value().id);
		}
		catch (const db::DatabaseFailure& e)
		{
			return FormErrorResponse(
				NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
				"Such verification code was not removed because database error occurred");
		}
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Verification code not found");
	}
	else
	{
		if (dto.code == verification.value().code)
		{
			try
			{
				m_facade->UpdateUserPassword(request.uid, password_hash, salt);
			}
			catch (const db::DatabaseFailure& e)
			{
				return FormErrorResponse(
					NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
					"Such user was not updated because database error occurred");
			}
			try
			{
				m_facade->RemoveVerificationCode(verification.value().id);
			}
			catch (const db::DatabaseFailure& e)
			{
				return FormErrorResponse(
					NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
					"Such verification code was not removed because database error occurred");
			}

			//RELOGIN
			auto user = m_facade->GetUserById(request.uid);

			Poco::JWT::Token token;
			token.setType("JWT");
			token.payload().set("id", FormatId(user->id));
			token.payload().set("email", std::string(user->email));
			token.setIssuedAt(Poco::Timestamp());

			Poco::JWT::Signer signer(password_hash);
			std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);

			Token out_dto{jwt};
			return FormJSONResponse(m_formatter.Format(out_dto));
		}
	}

	return FormErrorResponse(
		NetError::Status::HTTP_UNAUTHORIZED,
		"Wrong verification code");
}

