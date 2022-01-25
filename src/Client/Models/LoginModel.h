#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Constants.h"
#include "Net/Message.h"

class LoginModel
{
public:
	LoginModel(const std::string& hostname) : m_hostname{hostname} {}

	class JSONFormatter
	{
	public:
		struct LoginInDTO
		{
			std::string login;
			std::string password;
		};

		QJsonDocument Format(const LoginInDTO& dto);
	};

	class JSONParser
	{
	public:
		struct LoginOutDTO
		{
			std::string token;
		};

		void Parse(QJsonObject json, LoginOutDTO& dto);
	};

	Net::Request FormRequest(JSONFormatter::LoginInDTO dto);
	JSONParser::LoginOutDTO ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};

