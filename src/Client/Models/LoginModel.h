#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>

#include "Net/Constants.h"
#include "Net/Message.h"
#include "Net/Types.h"

class LoginModel
{
public:
	LoginModel(const std::string& hostname) : m_hostname{hostname} {}

	class JSONFormatter
	{
	public:
		struct Credentials
		{
			std::string email;
			std::string password;
		};

		QJsonDocument Format(const Credentials& credentials);
	};

	class JSONParser
	{
	public:
		struct UserData
		{
			std::string token;
			IdType id;
		};

		void Parse(QJsonObject json, UserData& dto);
	};

	Net::Request FormRequest(JSONFormatter::Credentials credentials);
	JSONParser::UserData ParseResponse(const Net::Response& response);
	bool IsEmailValid(const QString& email);

private:
	const std::string& m_hostname;
	const QString REGEX_PATTERN = "^[A-Z0-9a-z._-]{1,}@(\\w+)(\\.(\\w+))(\\.(\\w+))?(\\.(\\w+))?$";

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};
