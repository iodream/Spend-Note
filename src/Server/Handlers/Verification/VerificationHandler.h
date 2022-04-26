#pragma once

#include <string>
#include <memory>

#include "../libdal/Types.h"

#include "../ICommandHandler.h"
#include "../Verification/EmailSender.h"

class VerificationHandler : public ICommandHandler
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
	VerificationHandler() = default;
	virtual ~VerificationHandler() override = default;

	Net::Response Handle(Net::Request& request) override;

private:
	JSONParser m_parser{};
};
