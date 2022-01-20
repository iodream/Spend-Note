#pragma once

#include <string>

#include "ICommandHandler.h"

class EchoHandler : public ICommandHandler
{
	class JSONParser
    {		
    public:
		struct DTO {
			std::string msg;
		};

		DTO Parse(const QJsonDocument& payload);
    };

	class JSONFormatter
    {
	public:
		struct DTO {
			std::string msg;
		};

		QJsonDocument Format(const DTO& dto);
    };

public:
    EchoHandler() {}
    virtual ~EchoHandler() override {}

	Net::Response Handle(Net::Request& request) override;

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};
