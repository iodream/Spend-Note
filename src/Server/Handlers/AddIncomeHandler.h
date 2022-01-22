#pragma once

#include <string>

#include "AuthorizedHandler.h"
#include "../libdal/Facade/IDbFacade.h"

class AddIncomeHandler : public AuthorizedHandler
{
	class JSONParser
	{
	public:
		Income dto;
		Income Parse(const QJsonDocument& json_doc);
	};

public:
	AddIncomeHandler(IDbFacade::Ptr facade);
	virtual ~AddIncomeHandler() override {};

	Net::Response AuthHandle(const Net::Request& request) override;

	JSONParser m_parser{};
	std::unique_ptr<IDbFacade> m_facade;
};
