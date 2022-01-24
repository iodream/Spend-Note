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
		};
		Credentials Parse(const QJsonDocument& payload);
	};
public:
	SignupHandler(IDbFacade::Ptr facade);
	virtual ~SignupHandler() override {}

	Net::Response Handle(Net::Request& request) override;

	JSONParser m_parser{};
};
