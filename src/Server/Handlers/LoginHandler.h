#pragma once

#include <string>
#include <memory>

#include "ICommandHandler.h"

class LoginHandler : public ICommandHandler
{
	class JSONFormatter
	{
	public:
		struct LoginDTO {
			std::string token;
		};

		QJsonDocument Format(const LoginDTO& dto);
	};
	class JSONParser
	{
	public:
		struct LoginDTO {
			std::string login;
			std::string passwd_hash;
		};
	LoginDTO Parse(const QJsonDocument& payload);

	};
public:
	LoginHandler(IDbFacade::Ptr facade);
	virtual ~LoginHandler() override {}

	Net::Response Handle(Net::Request& request) override;

	JSONFormatter m_formatter{};
	JSONParser m_parser{};
};
