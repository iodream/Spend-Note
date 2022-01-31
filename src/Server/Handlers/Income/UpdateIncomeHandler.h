#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Income.h"
#include "ParsersAndFormatters/IncomeJSONParser.h"

class UpdateIncomeHandler : public AuthorizedHandler
{

public:
	UpdateIncomeHandler(IDbFacade::Ptr facade);
	virtual ~UpdateIncomeHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	IncomeJSONParser m_parser{};
};
