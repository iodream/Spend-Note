#pragma once

#include <string>

#include "../libdal/Facade/IDbFacade.h"
#include "ParsersAndFormatters/IncomeJSONParser.h"
#include "ParsersAndFormatters/IncomeJSONFormatter.h"

class AddIncomeHandler : public AuthorizedHandler
{
public:
	AddIncomeHandler(IDbFacade::Ptr facade);
	virtual ~AddIncomeHandler() override {};

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	IncomeJSONParser m_parser{};
	IncomeJSONFormatter m_formatter{};
};
