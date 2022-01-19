#pragma once

#include <string>

#include "ICommandHandler.h"
#include "../libdal/dbfacade.h"

class LoginHandler : public ICommandHandler
{
	class JSONFormatter
	{
	public:
		struct DTO {
			std::string token;
		};

		QJsonDocument Format(const DTO& dto);
	};
	class JSONParser
	{
	public:
		struct DTO {
			std::string login;
			std::string passwd_hash;
		};
	DTO Parse(const QJsonDocument& playload);

	};
public:
	LoginHandler();
	virtual ~LoginHandler() override {}

	Net::Response Handle(Net::Request& request) override;

    JSONFormatter m_formatter{};
	JSONParser m_parser{};
	DbFacade m_facade;

};
