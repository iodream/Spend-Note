#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Income.h"

class UpdateIncomeHandler : public AuthorizedHandler
{
	class JSONParser
	{
	public:
		Income Parse(const QJsonDocument& payload);
	};

public:
	UpdateIncomeHandler(IDbFacade::Ptr facade);
	virtual ~UpdateIncomeHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONParser m_parser{};
};
