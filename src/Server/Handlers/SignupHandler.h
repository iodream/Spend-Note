#pragma once

#include <string>
#include <memory>

#include "../libdal/Types.h"

#include "ICommandHandler.h"

class SignupHandler : public ICommandHandler
{
	class JSONFormatter
	{
	public:
		struct DTO {
			IdType id;
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
		DTO Parse(const QJsonDocument& payload);
	};
public:
	SignupHandler(IDbFacade::Ptr facade);
	virtual ~SignupHandler() override {}

	Net::Response Handle(Net::Request& request) override;

	JSONFormatter m_formatter{};
	JSONParser m_parser{};
};
