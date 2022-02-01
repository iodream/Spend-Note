#pragma once

#include <string>
#include <memory>

#include "ICommandHandler.h"

class LoginHandler : public ICommandHandler
{
	class JSONFormatter
	{
	public:
		struct Token {
			std::string token;
		};

		QJsonDocument Format(const Token& dto);
	};
	class JSONParser
	{
	public:
		struct Login{
			std::string login;
			std::string passwd_hash;
		};
	Login Parse(const QJsonDocument& payload);

	};
public:
	LoginHandler();
	virtual ~LoginHandler() override {}

	Net::Response Handle(Net::Request& request) override;

	JSONFormatter m_formatter{};
	JSONParser m_parser{};
};
