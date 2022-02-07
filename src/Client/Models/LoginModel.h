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
		struct Credentials
		{
			std::string login;
			std::string password;
		};

		QJsonDocument Format(const Credentials& credentials);
	};

	class JSONParser
	{
	public:
		struct Token
		{
			std::string token;
		};

		void Parse(QJsonObject json, Token& dto);
	};

	Net::Request FormRequest(JSONFormatter::Credentials credentials);
	JSONParser::Token ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};
