#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "DTO/Login.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class LoginModel
{
public:
	LoginModel(const std::string& hostname) : m_hostname{hostname} {}

	class JSONFormatter
	{
	public:
		QJsonDocument Format(const LoginInDTO& dto);
	};

	class JSONParser
	{
	public:
		void Parse(QJsonObject json, LoginOutDTO& dto);
	};

	Net::Request FormRequest(LoginInDTO dto);
	LoginOutDTO  ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};

