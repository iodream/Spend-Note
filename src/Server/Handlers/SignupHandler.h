#pragma once

#include <string>
#include <memory>

#include "../libdal/Types.h"

#include "ICommandHandler.h"

class SignupHandler : public ICommandHandler
{
	class JSONParser
	{
	public:
		struct Credentials {
			std::string login;
			std::string passwd_hash;
			std::string salt;
		};
		Credentials Parse(const QJsonDocument& payload);
	};

	std::string CreateSalt();
public:
	SignupHandler();
	virtual ~SignupHandler() override {}

	Net::Response Handle(Net::Request& request) override;

	JSONParser m_parser{};
};
