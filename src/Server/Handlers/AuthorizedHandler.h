#pragma once

#include <string>

#include "ICommandHandler.h"

class AuthorizedHandler : public ICommandHandler
{
public:
	AuthorizedHandler(IDbFacade::Ptr facade);
	virtual ~AuthorizedHandler() override {}

private:
	class JSONParser
	{
	public:
		struct DTO {
			IdType id;
			std::string login;
			double iat;
		};
	DTO Parse(const QJsonDocument& payload);

	};

	QJsonDocument DecodeJWTTokenBody(const std::string& token);
	bool CheckAuthorization(Net::Request& request);
public:
	Net::Response Handle(Net::Request& request) override;
	virtual Net::Response AuthHandle(const Net::Request& request) = 0;
private:
	JSONParser m_parser;
};
