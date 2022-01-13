#pragma once

#include <string>

#include "ICommandHandler.h"

class AuthorizedHandler : public ICommandHandler
{
public:
	AuthorizedHandler() {}
	virtual ~AuthorizedHandler() override {}

	QJsonDocument DecodeJWTTokenBody(const std::string& token);
	bool CheckAuthorization(const Net::Request& request);
	Net::Response Handle(Net::Request& request) override;
	virtual Net::Response AuthHandle(const Net::Request& request) = 0;
};
