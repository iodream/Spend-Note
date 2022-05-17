#pragma once

#include <string>
#include <memory>

#include "../libdal/Types.h"

#include "../ICommandHandler.h"
#include "../Verification/EmailSender.h"
#include "VerificationCodeFormatter.h"

class AddVerificationHandler : public ICommandHandler
{
	class JSONParser
	{
	public:
		struct Verification {
			std::string email;
		};
		Verification Parse(const QJsonDocument& payload);
	};
public:
	AddVerificationHandler() = default;
	virtual ~AddVerificationHandler() override = default;

	Net::Response Handle(Net::Request& request) override;

private:
	JSONParser m_parser{};
	VerificationCodeFormatter m_code_formatter{};
	EmailSender m_sender{};
	const size_t code_length = 6;
};
