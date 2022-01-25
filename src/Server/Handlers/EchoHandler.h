#pragma once

#include <string>

#include "ICommandHandler.h"

class EchoHandler : public ICommandHandler
{
	class JSONParser
    {		
    public:
		struct Message {
			std::string msg;
		};

		Message Parse(const QJsonDocument& payload);
    };

	class JSONFormatter
    {
	public:
		struct Message {
			std::string msg;
		};

		QJsonDocument Format(const Message& dto);
    };

public:
	EchoHandler(IDbFacade::Ptr facade) : ICommandHandler(std::move(facade)) {}
    virtual ~EchoHandler() override {}

	Net::Response Handle(Net::Request& request) override;

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};
