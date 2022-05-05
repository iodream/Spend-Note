#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>

#include "Net/Constants.h"
#include "Net/Message.h"

class SignupModel
{
public:
	struct SignupInDTO
	{
		std::string email;
		std::string password, pass_repeat;
	};

	class JSONFormatter
	{
	public:
		QJsonDocument Format(const SignupInDTO& dto);
	};

	SignupModel(const std::string& hostname) : m_hostname{hostname} {}
	Net::Request FormRequest(const SignupInDTO& dto);

	bool CheckPassRepeat(const SignupInDTO& dto) const;
	bool CheckData(const SignupInDTO& dto) const;
	bool IsEmailValid(const SignupInDTO& dto) const;

private:
	const std::string& m_hostname;
	const QString REGEX_PATTERN = "^[A-Z0-9a-z._-]{1,}@(\\w+)(\\.(\\w+))(\\.(\\w+))?(\\.(\\w+))?$";

	JSONFormatter m_formatter{};
};
