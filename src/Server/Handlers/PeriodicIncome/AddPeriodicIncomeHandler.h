#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/PeriodicIncome.h"

class AddPeriodicIncomeHandler : public AuthorizedHandler
{
public:
	AddPeriodicIncomeHandler();
	virtual ~AddPeriodicIncomeHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	PeriodicIncomeJSONParser m_parser{};
	PeriodicIncomeIdJSONFormatter m_formatter{};
};
