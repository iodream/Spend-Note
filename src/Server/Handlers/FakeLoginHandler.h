#pragma once

#include <string>

#include "ICommandHandler.h"

class FakeLoginHandler : public ICommandHandler
{
	class JSONFormatter
	{
	public:
		struct DTO {
			std::string token;
		};

		QJsonDocument Format(const DTO& dto);
	};

public:
    FakeLoginHandler() {}
    virtual ~FakeLoginHandler() override {}

	Net::Response Handle(Net::Request& request) override;

    JSONFormatter m_formatter{};
};
