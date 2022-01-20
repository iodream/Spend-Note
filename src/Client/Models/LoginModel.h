#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>

#include "DTO/Login.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class LoginModel
{
public:
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

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};

