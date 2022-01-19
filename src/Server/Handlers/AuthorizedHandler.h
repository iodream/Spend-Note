#pragma once

#include <string>

#include "ICommandHandler.h"
#include "../libdal/dbfacade.h"

class AuthorizedHandler : public ICommandHandler
{
public:
	AuthorizedHandler();
	virtual ~AuthorizedHandler() override {}

	class JSONParser
	{
	public:
		struct DTO {
			IdType id;
			std::string login;
			std::string iat;
		};
	DTO Parse(const QJsonDocument& payload);

	};

	QJsonDocument DecodeJWTTokenBody(const std::string& token);
	bool CheckAuthorization(Net::Request& request);
	Net::Response Handle(Net::Request& request) override;
	virtual Net::Response AuthHandle(const Net::Request& request) = 0;
	DbFacade m_facade;
	JSONParser m_parser;
};
