#pragma once

#include <string>
#include <memory>

#include "../libdal/Types.h"

#include "ICommandHandler.h"
#include "Verification/EmailSender.h"

class SignupHandler : public ICommandHandler
{
	class JSONParser
	{
	public:
		struct Credentials {
			std::string email;
			std::string password;
			std::string password_hash;
			std::string salt;
		};
		Credentials Parse(const QJsonDocument& payload);
	};

public:
	SignupHandler();
	virtual ~SignupHandler() override {}

	Net::Response Handle(Net::Request& request) override;

private:
	const size_t code_length = 6;
	JSONParser m_parser{};
};
