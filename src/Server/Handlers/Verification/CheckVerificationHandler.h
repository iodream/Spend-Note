#pragma once

#include <string>
#include <memory>

#include "../libdal/Types.h"

#include "../ICommandHandler.h"
#include "../Verification/EmailSender.h"

class CheckVerificationHandler : public ICommandHandler
{
	class JSONParser
	{
	public:
		struct Verification {
			std::string email;
			std::string code;
		};
		Verification Parse(const QJsonDocument& payload);
	};
public:
	CheckVerificationHandler() = default;
	virtual ~CheckVerificationHandler() override = default;

	Net::Response Handle(Net::Request& request) override;

private:
	JSONParser m_parser{};
};
