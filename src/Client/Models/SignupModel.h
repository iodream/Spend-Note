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
		std::string login;
		std::string password, pass_repeat;
		std::string passwd_hash;
	};

	class JSONFormatter
	{
	public:
		QJsonDocument Format(const SignupInDTO& dto);
	};

	SignupModel(const std::string& hostname) : m_hostname{hostname} {}
	Net::Request FormRequest(SignupInDTO dto);

	bool CheckPassRepeat(const SignupInDTO& dto) const;
	bool CheckData(const SignupInDTO& dto) const;

private:
	const std::string& m_hostname;
	JSONFormatter m_formatter{};
};
